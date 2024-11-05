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


int	mutex_get_value(t_mutex mutex)
{
	int	value;

	value = *mutex.value;
	return (value);	
}

int	mutex_set_value(t_mutex mutex, int *value)
{
	return (*mutex.value = *value, *mutex.value);
}


t_mutex	new_mutex(t_solib *solib, int locked, int value)
{
	t_mutex	fork;

	fork.acces = somalloc(solib, sizeof(pthread_mutex_t));
	fork.finish = somalloc(solib, sizeof(int));
	fork.locked = somalloc(solib, sizeof(int));
	fork.value = somalloc(solib, sizeof(int));
	fork.eat = somalloc(solib, sizeof(int));
	fork.time = somalloc(solib, sizeof(long));
	pthread_mutex_init(fork.acces, NULL);
	*fork.locked = locked;
	*fork.eat = 0;
	*fork.finish = 0;
	*fork.time = get_millis();
	*fork.value = value;
	return (fork);
}

t_mutex	*new_mutexs(t_solib *solib, int nbr, int locked, int value)
{
	t_mutex	*forks;
	int	i;

	i = -1;
	forks = somalloc(solib, sizeof(t_mutex) * nbr);
	while (++i < nbr)
		forks[i] = new_mutex(solib, locked, value);
	return (forks);
}

int	mutex(t_mutex mutex, int (*callback)(), void *data)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(mutex.acces);
	if (callback)
	{
		ret = callback(mutex, data);
	}
	pthread_mutex_unlock(mutex.acces);
	return (ret);
}