/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sosync_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:40:08 by marvin            #+#    #+#             */
/*   Updated: 2024/11/05 19:40:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sothread/all.h>

long	get_millis(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

t_sothread	*sonew_thread(t_sothsync *sync, int (*callback)(),
		int (*calldeath)(), void *data)
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

t_sothsync	*sothread(t_sothsync *sync, int (*callback)(),
		int (*calldeath)(), void *data)
{
	if (!sync)
		return (NULL);
	sync->threads[0] = sonew_thread(sync, callback, calldeath, data);
	sync->threads[0]->fork = sync->forks[0];
	if (pthread_create(&sync->threads[0]->instance, NULL,
			sothread_routine, sync->threads[0]))
		return (solib_close(sync->solib, 1), NULL);
	pthread_detach(sync->threads[0]->instance);
	return (sync);
}

t_sothsync	*sothreads(t_sothsync *sync, int (*callback)(),
		int (*calldeath)(), void *data)
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
		if (pthread_create(&sync->threads[i]->instance, NULL,
				sothread_routine, sync->threads[i]))
			return (solib_close(sync->solib, 1), NULL);
		pthread_detach(sync->threads[i]->instance);
	}
	return (sync);
}
