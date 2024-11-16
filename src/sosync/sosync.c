/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:08:01 by marvin            #+#    #+#             */
/*   Updated: 2024/06/05 18:08:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sothread/all.h>
#include <solibft/sostdlib.h>

int	thsync_syncro(t_sothsync *sync, long starting)
{
	int	i;

	if (thsync_death(sync, sync->forks, starting))
		return (1);
	i = -1;
	while (++i < sync->nbr)
		pthread_mutex_lock(sync->forks[i].instance);
	i = -1;
	while (++i < sync->nbr)
		thsync_finish(sync, i, sync->forks);
	i = -1;
	while (++i < sync->nbr)
		thsync_work(sync, i, sync->forks, starting);
	i = -1;
	while (++i < sync->nbr)
		pthread_mutex_unlock(sync->forks[i].instance);
	return (0);
}

t_fork	*new_thfork(t_solib *solib, long timeout)
{
	t_fork	*fork;

	fork = somalloc(solib, sizeof(t_fork));
	fork->timeout = timeout;
	fork->work = 0;
	fork->death = timeout;
	fork->stop = 0;
	return (fork);
}

t_mutex	*new_thsync_fork(t_solib *solib, int nbr, long timeout)
{
	t_mutex	*mutex;
	int		i;

	i = -1;
	mutex = somalloc(solib, sizeof(t_mutex) * nbr);
	while (++i < nbr)
		mutex[i] = new_mutex(solib, new_thfork(solib, timeout), 0);
	return (mutex);
}

t_sothsync	*sothsync(t_solib *solib, int nbr, int syncro, char *timeout)
{
	t_sothsync	*sync;
	int			*ret;

	if (nbr < 1)
		return (NULL);
	sync = somalloc(solib, sizeof(t_sothsync));
	sync->start = somalloc(solib, sizeof(pthread_mutex_t));
	ret = somalloc(solib, sizeof(int));
	*ret = 0;
	sync->threads = somalloc(solib, sizeof(t_sothread *) * (nbr + 1));
	sync->threads[nbr] = NULL;
	pthread_mutex_init(sync->start, NULL);
	sync->forks = new_thsync_fork(solib, nbr, ft_atoi(timeout));
	sync->acces = new_mutex(solib, ret, 0);
	sync->solib = solib;
	sync->nbr = nbr;
	sync->syncro = syncro;
	pthread_mutex_lock(sync->start);
	if (pthread_create(&sync->instance, NULL, sothsync_routine, sync))
		return (solib->close(solib, 1), NULL);
	pthread_detach(sync->instance);
	return (sync);
}

void	*sothsync_routine(void *arg)
{
	t_sothsync	*sync;
	long		starting;
	int			value;

	sync = (t_sothsync *)arg;
	pthread_mutex_lock(sync->acces.instance);
	pthread_mutex_lock(sync->start);
	pthread_mutex_unlock(sync->start);
	starting = get_millis();
	*sync->acces.starting = starting;
	value = *sync->acces.locked;
	pthread_mutex_unlock(sync->acces.instance);
	while (!value)
	{
		if (thsync_syncro(sync, starting))
			break ;
		value = *(int *)mutget(sync->acces, sync->acces.locked);
	}
	pthread_mutex_lock(sync->acces.instance);
	*(int *)(sync->acces.data) = 1;
	pthread_mutex_destroy(sync->start);
	free_mutexs(sync->solib, sync->nbr, sync->forks);
	pthread_mutex_unlock(sync->acces.instance);
	return (NULL);
}
