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


void	free_mutex(t_solib *solib, t_mutex mutex)
{
	pthread_mutex_lock(mutex.instance);
	sofree(solib, mutex.locked);
	sofree(solib, mutex.use);
	sofree(solib, mutex.last);
	sofree(solib, mutex.starting);
	pthread_mutex_unlock(mutex.instance);
	pthread_mutex_destroy(mutex.instance);
}

void	free_mutexs(t_solib *solib, int nbr, t_mutex *mutex)
{
	int	i;

	i = -1;
	while (++i < nbr)
		free_mutex(solib, mutex[i]);
}

t_mutex	new_mutex(t_solib *solib, void *data, int locked)
{
	t_mutex	mutex;

	mutex.instance = somalloc(solib, sizeof(pthread_mutex_t));
	mutex.locked = somalloc(solib, sizeof(int));
	mutex.use = somalloc(solib, sizeof(int));
	mutex.last = somalloc(solib, sizeof(long));
	mutex.starting = somalloc(solib, sizeof(long));
	*mutex.locked = 0;
	*mutex.use = 0;
	*mutex.last = 0;
	*mutex.starting = get_millis();
	mutex.data = data;
	pthread_mutex_init(mutex.instance, NULL);
	if (locked)
		pthread_mutex_lock(mutex.instance);
	return (mutex);
}

t_mutex	*new_mutexs(t_solib *solib, int nbr, void *data, int locked)
{
	t_mutex	*mutex;
	int	i;

	i = -1;
	mutex = somalloc(solib, sizeof(t_mutex) * nbr);
	while (++i < nbr)
		mutex[i] = new_mutex(solib, data, locked);
	return (mutex);
}

int	mutex(t_mutex mutex, int (*callback)(), void *data)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(mutex.instance);
	if (callback)
		ret = callback(mutex, data);
	pthread_mutex_unlock(mutex.instance);
	return (ret);
}

void	*mutget(t_mutex mutex, void *data)
{
	void	*ret;

	pthread_mutex_lock(mutex.instance);
	if (data)
		ret = data;
	else
		ret = NULL;
	pthread_mutex_unlock(mutex.instance);
	return (ret);
}

int	mutset(t_mutex mutex, int (*callback)(), void *dst, void *src)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(mutex.instance);
	if (callback)
		ret = callback(mutex, dst, src);
	pthread_mutex_unlock(mutex.instance);
	return (ret);
}