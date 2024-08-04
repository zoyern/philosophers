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
#include <sotypes/soprintf.h>
#include <solibft/sostdlib.h>

int		call_mutex(pthread_mutex_t *mutex, int (*callback)(), void *data)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(mutex);
	if (callback)
		ret = callback(data);
	pthread_mutex_unlock(mutex);
	return (ret);
}

t_sotimer	**create_timers(t_solib *solib, t_soloop *loop, char **strs)
{
	t_sotimer	**timers;
	int			i;	

	i = 0;
	while (strs[i])
		i++;
	timers = solib->malloc(solib, sizeof(t_sotimer *) * (i + 1));
	i = 0;
	while (strs[i])
	{
		if (i < 2)
			timers[i] = loop->timers->new(loop, 1, ft_atoi(strs[i]));
		else
			timers[i] = loop->timers->new(loop, 0, ft_atoi(strs[i]));
		i++;
	}
	timers[i] = NULL;
	return (timers);
}