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

int	thsync_glouton(t_sothsync *sync, int id, t_mutex *mutex)
{
	int	i;

	i = 0;
	while (++i < sync->syncro)
	{
		if (protect_modulo(id + i, sync->nbr) == id)
			return (1);
		if (*mutex[protect_modulo(id + i, sync->nbr)].locked)
			return (1);
		if ((*mutex[id].use > *mutex[protect_modulo(id - i, sync->nbr)].use
				|| *mutex[id].last > *mutex[protect_modulo(id - i,
						sync->nbr)].last)
			&& !((t_fork *)(mutex[protect_modulo(id - i,
						sync->nbr)].data))->stop)
			return (1);
		if ((*mutex[id].use > *mutex[protect_modulo(id + i, sync->nbr)].use
				|| *mutex[id].last > *mutex[protect_modulo(id + i,
						sync->nbr)].last)
			&& !((t_fork *)(mutex[protect_modulo(id + i,
						sync->nbr)].data))->stop)
			return (1);
	}
	return (0);
}

void	thsync_finish(t_sothsync *sync, int id, t_mutex *mutex)
{
	t_fork	*fork;

	if (!mutex && !mutex[id].data)
		return ;
	fork = mutex[id].data;
	if (fork && fork->finish)
		thsync_unlock(sync, id, mutex);
}

void	thsync_work(t_sothsync *sync, int id, t_mutex *mutex, long starting)
{
	t_fork	*fork;

	fork = mutex[id].data;
	if (!*mutex[id].locked && !fork->work && !fork->stop
		&& !thsync_glouton(sync, id, mutex))
		thsync_lock(sync, id, mutex, starting);
}

void	thsync_calldeath(t_sothsync *sync, int id, long time)
{
	if (sync->threads[id]->calldeath)
		sync->threads[id]->calldeath(time, id, sync, sync->threads);
}

int	thsync_death(t_sothsync *sync, t_mutex *mutex, long starting)
{
	int		i;
	int		count;
	t_fork	*fork;

	i = -1;
	count = 0;
	while (++i < sync->nbr)
	{
		pthread_mutex_lock(mutex[i].instance);
		pthread_mutex_lock(sync->acces.instance);
		fork = mutex[i].data;
		if (fork->stop < 0
			|| (get_millis() - starting > fork->death && !fork->stop))
			return (fork->stop = 1, thsync_calldeath(sync, i,
					get_millis() - starting),
				multiple_unlock(sync, mutex, i, -1));
		if (fork->stop)
			count++;
		if (count == sync->nbr)
			return (multiple_unlock(sync, mutex, i, 1));
		pthread_mutex_unlock(sync->acces.instance);
		pthread_mutex_unlock(mutex[i].instance);
	}
	return (0);
}
