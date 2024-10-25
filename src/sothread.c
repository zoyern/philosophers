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

long	correct_time(long current, long *starting, long last)
{
	long	millis;

	millis = current - *starting;
	if (millis - last > 1)
		return (*starting += millis - last,
			(millis -= (millis - last) + 1), millis);
	return (millis);
}

long	get_millis(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

/*

long	get_millis(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	sof(int f2, int func, int f1)
{
	return ((void)f2, (void)f1, func);
}

int	mutlock(t_mutex *mutex)
{
	return (pthread_mutex_lock(mutex->instance), mutex->lock = 1);
}
int	mutend(t_mutex *mutex)
{
	return (mutex->lock = 0, pthread_mutex_unlock(mutex->instance));
}

int	thread_kill(t_thread *thread)
{
	sof(mutend(thread->sync->time),
	sof(mutend(thread->sync->print),
			soprintf("%ld %d died\n", *thread->millis),
			mutlock(thread->sync->print)),
			mutlock(thread->sync->time));
	return (*thread->alive = 0, *thread->value = -1, -1);
}

int	thread_end(t_thread *thread)
{
	sof(mutend(thread->sync->time),
	sof(mutend(thread->sync->print),
			soprintf("%ld %d close\n", *thread->millis),
			mutlock(thread->sync->print)),
			mutlock(thread->sync->time));
	return (*thread->alive = 0, *thread->value = 0, 0);
}

t_mutex *new_mutex(t_solib *solib, int locked)
{
    t_mutex *mutex;

    mutex = somalloc(solib, sizeof(t_mutex));
	mutex->instance = somalloc(solib, sizeof(pthread_mutex_t));
	pthread_mutex_init(mutex->instance, NULL);
    mutex->lock = locked;
    if (locked)
		mutlock(mutex);
    return (mutex);
}

int	update_time(t_thread *thread)
{
	return (*thread->millis = get_millis() - *thread->sync->starting, 0);
}

int	thread_close(t_thread *thread, int ret)
{
	if (ret < 0) // exit error ferme tout
		return (mutend(thread->sync->die), thread_kill(thread), mutlock(thread->sync->die), -1);
	if (ret) // exit error ferme tout
		return (mutend(thread->sync->die), thread_end(thread), mutlock(thread->sync->die), -1);
	return (ret);
}

int	take_fork(t_thread *thread)
{
	(void)thread;
	return (0);
}

int	check_syncro(t_thread *thread)
{
	sof(mutend(thread->sync->start), take_fork(thread) , mutlock(thread->sync->start));
	return (0);
}

void* thread_routine(void* arg)
{
    t_thread *thread = (t_thread *)arg;  // Cast de l'argument en entier
	int	condition_ret;
	int	routine_ret;

	while (sof(mutend(thread->sync->die), *thread->alive , mutlock(thread->sync->die)))
	{
		if (thread->condition)
			condition_ret = thread->condition(thread, thread->data);
		if (!condition_ret) // exit error ferme tout
			thread_close(thread, condition_ret);
		check_syncro(thread);
		if (sof(mutend(thread->sync->start), *thread->sync->work , mutlock(thread->sync->start)))
		{
			if (thread->routine)
				routine_ret = thread->routine(thread, thread->data);
			if (!routine_ret) // exit error ferme tout
				thread_close(thread, routine_ret);
		}
		sof(mutend(thread->sync->time), update_time(thread), mutlock(thread->sync->time));
	}
    return (NULL);
}


t_sync	*thread_sync(t_solib *solib, void *data, int lock, t_sync *cpsync)
{
	t_sync	*sync;

	sync = somalloc(solib, sizeof(t_sync));
	sync->data = data;
	sync->work = somalloc(solib, sizeof(int));
	sync->value = somalloc(solib, sizeof(int));
	*sync->value = 0;
	if (!cpsync)
	{
		sync->id = -1;
		sync->starting = somalloc(solib, sizeof(long));
		sync->nbr = somalloc(solib, sizeof(int));
		sync->syncro = somalloc(solib, sizeof(int));
		sync->millis = somalloc(solib, sizeof(long));
		sync->loop = somalloc(solib, sizeof(long));
		sync->work = somalloc(solib, sizeof(int));
		sync->fork = somalloc(solib, sizeof(int));
		*sync->starting = get_millis();
		*sync->fork = 1;
		*sync->millis = 0;
		*sync->nbr = 1;
		*sync->loop = 0;
		*sync->work = 1;
		sync->start = new_mutex(solib, lock);
		sync->print = new_mutex(solib, 0);
		sync->die = new_mutex(solib, 0);
		sync->time = new_mutex(solib, 0);
		*sync->syncro = 1;
		return (sync);
	}
	sync->fork = cpsync->fork;
	sync->id = cpsync->id + 1;
	sync->starting = cpsync->starting;
	sync->millis = cpsync->millis;
	sync->start = cpsync->start;
	sync->nbr = cpsync->nbr;
	sync->print = cpsync->print;
	sync->die = cpsync->die;
	sync->time = cpsync->time;
	sync->syncro = cpsync->syncro;
	return (sync);
}

t_thread	*new_threads(t_solib *solib,  int nbr, int syncro, t_thread *cpthread)
{
	t_thread	**thread;
	int			i;

	if (!cpthread)
		return (NULL);
	thread = somalloc(solib, sizeof(t_thread *) * (nbr + 1));
	thread[nbr] = NULL;
	i = -1;
	*cpthread->sync->nbr = nbr;
	*cpthread->sync->syncro = syncro;
	sofree(solib, cpthread->sync->fork);
	cpthread->sync->fork = somalloc(solib, sizeof(int) * (syncro));
	while (++i < syncro)
		cpthread->sync->fork[i] = 1;
	i = 0;
	thread[i] = new_thread(solib, cpthread->condition, cpthread->routine,
				thread_sync(solib, cpthread, 1, cpthread->sync));
	while (++i < nbr)
		thread[i] = new_thread(solib, thread[i - 1]->condition, thread[i - 1]->routine,
				thread_sync(solib, thread[i - 1], 1, thread[i - 1]->sync));
	i = -1;
	while (++i < nbr)
	{
		if (pthread_create(&thread[i]->sync->instance, NULL, thread_routine, thread[i]))
       		return (solib->close(solib, 1), NULL);
    	pthread_detach(thread[i]->sync->instance);
	}
	mutend(cpthread->sync->start);
	return (cpthread);
}

t_thread	*new_thread(t_solib *solib,  int (*condition)() , int (*routine)(), t_sync *sync)
{
	t_thread	*thread;

	thread = somalloc(solib, sizeof(t_thread));
	thread->alive = somalloc(solib, sizeof(int));

	thread->sync = sync;
	thread->id = sync->id;
	thread->data = sync->data;
	thread->value = sync->value;
	*thread->alive = 1;
	thread->millis = sync->millis;
	thread->routine = routine;
	thread->condition = condition;
	if (pthread_create(&thread->sync->instance, NULL, thread_routine, thread))
        return (NULL);
    pthread_detach(thread->sync->instance);
	return (thread);
}



int	wait_thread(t_thread *thread, int blocked)
{
	if (!blocked)
		return (sof(mutend(thread->sync->die), *thread->value, mutlock(thread->sync->die)));
	while (sof(mutend(thread->sync->die), *thread->alive, mutlock(thread->sync->die)))
		continue;
	return (sof(mutend(thread->sync->die), *thread->value, mutlock(thread->sync->die)));
}
*/

