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

int		check_eat(int id, int max, t_mutex *fork)
{
	int	i;
	int	value;
	long	time;

	i = -1;
	pthread_mutex_lock(fork[id].acces);
	value = *fork[id].eat;
	time = *fork[id].time;
	pthread_mutex_unlock(fork[id].acces);
	while (++i < max)
	{
		pthread_mutex_lock(fork[i].acces);
		if (time > *fork[i].time)
		{
			if (value > *fork[i].eat)			
				return (pthread_mutex_unlock(fork[i].acces), 1);
		}
		pthread_mutex_unlock(fork[i].acces);
	}
	return (0);
}

int get_fork(int id, int syncro, int max, t_mutex *fork)
{
    if (!syncro)
        return (1);
    pthread_mutex_lock(fork[id % max].acces);
	if (!*fork[id % max].locked)
	{
		*fork[id % max].locked = 1;
		pthread_mutex_unlock(fork[id % max].acces);
		if (get_fork(id + 1, syncro - 1, max, fork))
			return (1);
		pthread_mutex_lock(fork[id % max].acces);
		*fork[id % max].locked = 0;
	}
	pthread_mutex_unlock(fork[id % max].acces);
    return (0);
}

int		reset_fork(int id, int syncro, int max, t_mutex *fork)
{
	int	i;

	pthread_mutex_lock(fork[id].acces);
	if (*fork[id].finish)
	{
		*fork[id].finish = 0;
		pthread_mutex_unlock(fork[id].acces);
		i = -1;
		while (++i < syncro)
		{
			pthread_mutex_lock(fork[(id + i) % max].acces);
			*fork[(id + i) % max].locked = 0;
			pthread_mutex_unlock(fork[(id + i) % max].acces);
		}
		return (1);
	}
	pthread_mutex_unlock(fork[id].acces);
	return (0);
}
