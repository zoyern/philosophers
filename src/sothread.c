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







//attente de la fin des thread avec le monitor
int	wait_sothread(t_sothsync *sync, int (*callback)(), void *data, int *status)
{
	int		value;

	(void)sync;
	(void)callback;
	(void)data;
	(void)status;
	value = 0;
	if (!sync)
		return (0);
	while (!(*(int *)mutget(sync->acces, sync->acces.data)))
	{
		if (callback)
			callback(sync, data);
	}
	return (value);
}


//creation de la structure d'un thread simple
t_sothread	*sonew_thread(t_sothsync *sync, int (*callback)(), int (*calldeath)(), void *data)
{
	t_sothread	*thread;

	if (!sync)
		return (NULL);
	thread = somalloc(sync->solib, sizeof(t_sothread));
	thread->solib = sync->solib;
	thread->id = 0;
	thread->millis = 0;
	thread->data = data;
	thread->nbr = sync->nbr;
	thread->callback = callback;
	thread->calldeath = calldeath;
	thread->acces = sync->acces;
	thread->start = sync->start;
	return (thread);
}

//creation d'un seul thread avec son monitor ascocier
t_sothsync	*sothread(t_sothsync *sync, int (*callback)(), int (*calldeath)(), void *data)
{

	if (!sync)
		return (NULL);
	sync->threads[0] = sonew_thread(sync, callback, calldeath, data);
	sync->threads[0]->fork = sync->forks[0];
	if (pthread_create(&sync->threads[0]->instance, NULL, sothread_routine, sync->threads[0]))
       	return (solib_close(sync->solib, 1), NULL);
    pthread_detach(sync->threads[0]->instance);
	return (sync);
}

//creation de plusieurs threads a partir de sync déclare un timeout (time to death) la routine et une data en l'occurence philo
t_sothsync	*sothreads(t_sothsync *sync, int (*callback)(), int (*calldeath)(), void *data)
{
	int	i;

	if (!sync)
		return (NULL);
	i = -1;
	while (++i < sync->nbr)
	{
		sync->threads[i] = sonew_thread(sync, callback, calldeath, data);
		sync->threads[i]->id = i;
		sync->threads[i]->fork = sync->forks[i];
		//sothread_routine est le callback par default pour tout les thread
		if (pthread_create(&sync->threads[i]->instance, NULL, sothread_routine, sync->threads[i]))
       		return (solib_close(sync->solib, 1), NULL);
    	pthread_detach(sync->threads[i]->instance);
	}
	return (sync);
}


void	correct_delay(t_sothread *thread, t_fork *fork, long delay)
{
	fork->death += delay;
	pthread_mutex_unlock(thread->fork.instance);
}

int	get_work(t_sothread *thread, t_fork *fork)
{
	int	ret;

	pthread_mutex_lock(thread->fork.instance);
	ret = fork->work;
	pthread_mutex_unlock(thread->fork.instance);
	return (ret);
}




// le callback des routine qui doit d'occuper de verifier la mort et lancer la routine utilisateur 
// si il a sa fouchette a value 1 reset la mort avec le temps actuelle plus le timeout de base



int	sothread_close(t_sothread *thread, int ret)
{
	t_fork	*fork;

	fork = thread->fork.data;
	fork->stop = ret;
	return (ret);
}

void* sothread_routine(void* arg)
{
    t_sothread *thread = (t_sothread *)arg;  // Cast de l'argument en entier
	long		starting;
	long		spawn_point;

	if (thread->id == thread->nbr - 1)
		pthread_mutex_unlock(thread->start);
	starting = *(long *)mutget(thread->acces, thread->acces.starting);
	spawn_point = get_millis() - starting;
	correct_delay(thread, thread->fork.data, spawn_point);
	while (!(*(int *)mutget(thread->acces, thread->acces.locked)))
	{
		if (get_work(thread, thread->fork.data))
		{
			pthread_mutex_lock(thread->fork.instance);
			thread->millis = get_millis() - starting;
			if (thread->callback)
				if (sothread_close(thread, thread->callback(thread, thread->data)))
					return (pthread_mutex_unlock(thread->fork.instance), NULL);
			pthread_mutex_unlock(thread->fork.instance);
		}
	}
    return (NULL);
}