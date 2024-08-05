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

#include <philosophers/all.h>
#include <solibft/sostdlib.h>

int		call_mutex(pthread_mutex_t *mutex, int (*callback)(), void *data, void *data2)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(mutex);
	if (callback)
		ret = callback(data, data2);
	pthread_mutex_unlock(mutex);
	return (ret);
}

int		check_death_all(int **lifeguard)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	while (lifeguard[len])	
		len++;
	while (lifeguard[i] && *lifeguard[i])
		i++;
	if (i == len)
		return (1);
	return (0);
}

int		check_death_one(int **lifeguard)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	while (lifeguard[len])	
		len++;
	while (lifeguard[i] && !*lifeguard[i])
		i++;
	if (i == len)
		return (1);
	return (0);
}