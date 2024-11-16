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

int	protect_modulo(int nbr, int mod)
{
	if (nbr > -1)
		return (nbr % mod);
	return (protect_modulo(mod - nbr, mod));
}

void	th_free(t_sothread *thread)
{
	t_fork	*fork;

	fork = thread->fork.data;
	fork->finish = 1;
}

int	th_wait(t_sothread *thread, int exit)
{
	t_fork	*fork;

	fork = thread->fork.data;
	fork->work = 0;
	fork->stop = exit;
	return (exit);
}

void	thsync_lock(t_sothsync *sync, int id, t_mutex *mutex, long starting)
{
	int		i;
	t_fork	*fork;

	i = -1;
	fork = mutex[id].data;
	fork->work = 1;
	fork->death = (get_millis() - starting) + fork->timeout;
	(*mutex[id].use)++;
	*mutex[id].last = (get_millis() - starting) + 1;
	while (++i < sync->syncro)
	{
		soprintf("%ld \t%d\thas taken a fork\n",
			get_millis() - starting, id + 1);
		*mutex[protect_modulo(id + i, sync->nbr)].locked = 1;
	}
	soprintf("%ld \t%d\tis eating\n", get_millis() - starting, id + 1);
}

void	thsync_unlock(t_sothsync *sync, int id, t_mutex *mutex)
{
	int		i;
	t_fork	*fork;

	i = -1;
	fork = mutex[id].data;
	fork->finish = 0;
	while (++i < sync->syncro)
		*mutex[protect_modulo(id + i, sync->nbr)].locked = 0;
}
