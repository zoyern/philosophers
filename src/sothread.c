/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 21:31:29 by marvin            #+#    #+#             */
/*   Updated: 2024/06/04 16:53:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sothread/all.h>
#include <solibft/sostdlib.h>

//attente de la fin des thread avec le monitor
int	wait_sothread(t_sothsync *sync)
{
	int		value;

	pthread_mutex_lock(sync->acces.acces);
	value = *sync->value;
	pthread_mutex_unlock(sync->acces.acces);
	while (!value)
	{
		pthread_mutex_lock(sync->acces.acces);
		value = *sync->value;
		pthread_mutex_unlock(sync->acces.acces);
	}
	return (value);
}


//creation de la structure d'un thread simple
t_sothread	*sonew_thread(t_sothsync *sync, long timeout, int (*callback)(), void *data)
{
	t_sothread	*thread;

	if (!sync)
		return (NULL);
	thread = somalloc(sync->solib, sizeof(t_sothread));
	thread->solib = sync->solib;
	thread->id = 0;
	thread->millis = 0;
	thread->value = sync->value;
	thread->timeout = timeout;
	thread->data = data;
	thread->callback = callback;
	thread->starting = sync->starting;
	thread->print = sync->print;
	thread->acces = sync->acces;
	thread->thread_acces = sync->thread_acces;
	return (thread);
}

//creation d'un seul thread avec son monitor ascocier
t_sothsync	*sothread(t_solib *solib, char *timeout, int (*callback)(), void *data)
{
	t_sothsync	*sync;
	
	sync = sothsync(solib, 1, 1);
	sync->threads[0] = sonew_thread(sync, ft_atoi(timeout), callback, data);
	sync->threads[0]->fork = sync->forks[0];
	if (pthread_create(&sync->threads[0]->instance, NULL, sothread_routine, sync->threads[0]))
       	return (solib->close(solib, 1), NULL);
    pthread_detach(sync->threads[0]->instance);
	pthread_mutex_unlock(sync->acces.acces);
	return (sync);
}

//creation de plusieurs threads a partir de sync déclare un timeout (time to death) la routine et une data en l'occurence philo
t_sothsync	*sothreads(t_sothsync *sync, char *timeout, int (*callback)(), void *data)
{
	int	i;

	if (!sync)
		return (NULL);
	i = -1;
	while (++i < sync->nbr)
	{
		sync->threads[i] = sonew_thread(sync, ft_atoi(timeout), callback, data);
		sync->threads[i]->id = i;
		sync->threads[i]->fork = sync->forks[i];
		if (pthread_create(&sync->threads[i]->instance, NULL, sothread_routine, sync->threads[i]))
       		return (sync->solib->close(sync->solib, 1), NULL);
    	pthread_detach(sync->threads[i]->instance);
	}
	pthread_mutex_unlock(sync->acces.acces);
	return (sync);
}

void* sothread_routine(void* arg)
{
    t_sothread *thread = (t_sothread *)arg;  // Cast de l'argument en entier
	long		starting;
	long		death;
	int			ret;
	int			flag;

	starting = 0;
	ret = 0;
	flag = 1;
	pthread_mutex_lock(thread->thread_acces.acces);
	starting = *thread->starting;
	pthread_mutex_unlock(thread->thread_acces.acces);
	thread->millis = get_millis() - starting;
	death = thread->millis + thread->timeout;
	while (thread->millis <= death + 10)
	{
		//mutex(thread->print, print_millis, thread);
		if (mutex(thread->fork, mutex_get_value, NULL))
		{
			if (flag)
			{
				death = (get_millis() - starting) + thread->timeout;
				flag = 0;
			}
			if (thread->callback)
				ret = thread->callback(thread, thread->data);
			if (ret)
				break ;
		}
		else
			flag = 1;
		thread->millis = get_millis() - starting;
	}
	if (thread->millis > death)
		ret = -1;
	if (ret < 0)
	{
		pthread_mutex_lock(thread->print.acces);
		soprintf("%ld \t%d\tdied\n", thread->millis, thread->id + 1);
		pthread_mutex_unlock(thread->print.acces);
		pthread_mutex_lock(thread->acces.acces);
		*thread->value = -1;
		pthread_mutex_unlock(thread->acces.acces);
	}
    return (NULL);
}