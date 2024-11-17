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

int	wait_sothread(t_sothsync *sync, int (*callback)(), void *data)
{
	int	value;
	int	i;

	if (!sync)
		return (0);
	value = *(int *)mutget(sync->acces, sync->acces.data);
	while (!value)
	{
		if (callback)
			callback(sync, data);
		value = *(int *)mutget(sync->acces, sync->acces.data);
	}
	free_mutex(sync->solib, sync->acces);
	i = -1;
	while (++i < sync->nbr)
		sofree(sync->solib, sync->threads[i]);
	sofree(sync->solib, sync->threads);
	sofree(sync->solib, sync);
	return (value);
}

long	correct_delay(t_sothread *thread, t_fork *fork)
{
	long	delay;
	long	starting;

	starting = *(long *)mutget(thread->acces, thread->acces.starting);
	delay = get_millis() - starting;
	fork->death += delay;
	fork->timeout += delay;
	pthread_mutex_unlock(thread->fork.instance);
	return (starting);
}

int	get_work(t_sothread *thread, t_fork *fork, long starting)
{
	int	ret;

	pthread_mutex_lock(thread->fork.instance);
	ret = fork->work;
	thread->millis = get_millis() - starting;
	if (!ret)
		pthread_mutex_unlock(thread->fork.instance);
	return (ret);
}

int	sothread_close(t_sothread *thread, int ret)
{
	t_fork	*fork;

	fork = thread->fork.data;
	fork->stop = ret;
	return (ret);
}

void	*sothread_routine(void	*arg)
{
	t_sothread	*thread;
	long		starting;

	thread = (t_sothread *)arg;
	pthread_mutex_lock(thread->fork.instance);
	if (thread->id == thread->nbr - 1)
		pthread_mutex_unlock(thread->start);
	starting = correct_delay(thread, thread->fork.data);
	while (1)
	{
		if ((*(int *)mutget(thread->acces, thread->acces.locked)))
			break ;
		if (get_work(thread, thread->fork.data, starting))
		{
			if (thread->callback)
				if (sothread_close(thread,
						thread->callback(thread, thread->data)))
					return (pthread_mutex_unlock(thread->fork.instance), NULL);
			pthread_mutex_unlock(thread->fork.instance);
		}
	}
	pthread_mutex_lock(thread->fork.instance);
	sothread_close(thread, 1);
	pthread_mutex_unlock(thread->fork.instance);
	return (NULL);
}
