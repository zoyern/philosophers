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

void	thsync_lock(t_sothsync *sync, int id, t_mutex *mutex, long time)
{
	int	i;
	t_fork	*fork;
	
	i = -1;
	fork = mutex[id].data;
	fork->work = 1;
	fork->death = time + fork->timeout;
	(*mutex[id].use)++;
	*mutex[id].last = time + 1;
	while (++i < sync->syncro)
	{
		soprintf("%ld \t%d\thas taken a fork\n", time, id + 1);
		*mutex[protect_modulo(id + i, sync->nbr)].locked = 1;
	}
}

void	thsync_unlock(t_sothsync *sync, int id, t_mutex *mutex)
{
	int	i;
	t_fork	*fork;
	
	i = -1;
	fork = mutex[id].data;
	fork->finish = 0;
	while (++i < sync->syncro)
		*mutex[protect_modulo(id + i, sync->nbr)].locked = 0;
}

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
		if ((*mutex[id].use > *mutex[protect_modulo(id - i, sync->nbr)].use || *mutex[id].last > *mutex[protect_modulo(id - i, sync->nbr)].last) && !((t_fork *)(mutex[protect_modulo(id - i, sync->nbr)].data))->stop)
			return (1);
		if ((*mutex[id].use > *mutex[protect_modulo(id + i, sync->nbr)].use || *mutex[id].last > *mutex[protect_modulo(id + i, sync->nbr)].last) && !((t_fork *)(mutex[protect_modulo(id + i, sync->nbr)].data))->stop)
			return (1);
	}
	return (0);
}

void	thsync_finish(t_sothsync *sync, int id, t_mutex *mutex)
{
	t_fork	*fork;

	fork = mutex[id].data;
	if (fork && fork->finish)
		thsync_unlock(sync, id, mutex);
}

void	thsync_work(t_sothsync *sync, int id, t_mutex *mutex, long time)
{
	t_fork	*fork;

	fork = mutex[id].data;
	if (!*mutex[id].locked && !fork->work && !fork->stop && !thsync_glouton(sync, id, mutex))
		thsync_lock(sync, id, mutex, time);
}

void	thsync_calldeath(t_sothsync *sync, int id, long time)
{
	if (sync->threads[id]->calldeath)
		sync->threads[id]->calldeath(time, id, sync, sync->threads);
}

int	thsync_death(t_sothsync *sync, t_mutex *mutex, long time)
{
	int	i;
	int	count;
	t_fork	*fork;
	
	i = -1;
	count = 0;
	while (++i < sync->nbr)
	{
		pthread_mutex_lock(mutex[i].instance);
		pthread_mutex_lock(sync->acces.instance);
		fork = mutex[i].data;
		if (fork->stop < 0 || (time > fork->death && !fork->stop))
			return (*sync->acces.locked = 1, thsync_calldeath(sync, i, time), pthread_mutex_unlock(sync->acces.instance), pthread_mutex_unlock(mutex[i].instance), 1);
		if (fork->stop)
			count++;
		if (count == sync->nbr)
			*sync->acces.locked = 1;
		pthread_mutex_unlock(sync->acces.instance);
		pthread_mutex_unlock(mutex[i].instance);
	}
	return (0);
}

int	thsync_syncro(t_sothsync *sync, long time)
{
	int	i;

	if (thsync_death(sync, sync->forks, time))
		return (1);
	i = -1;
	while (++i < sync->nbr)
		pthread_mutex_lock(sync->forks[i].instance);
	i = -1;
	while (++i < sync->nbr)  // check si un fork est fini ou pas
		thsync_finish(sync, i, sync->forks);
	i = -1;
	while (++i < sync->nbr)
		thsync_work(sync, i, sync->forks, time);
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
	int	i;

	i = -1;
	mutex = somalloc(solib, sizeof(t_mutex) * nbr);
	while (++i < nbr)
		mutex[i] = new_mutex(solib, new_thfork(solib, timeout), 0);
	return (mutex);
}

// creation du monitor sync combien de thread il va géré avec la syncronisation (pour philosopher 2 mais peu etre 1, 4, 10 etc)
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


void* sothsync_routine(void* arg)
{
    t_sothsync *sync = (t_sothsync *)arg;  // Cast de l'argument en entier
	long	starting;
	int		value;

	pthread_mutex_lock(sync->acces.instance);
	pthread_mutex_lock(sync->start);
	pthread_mutex_unlock(sync->start);
	starting = get_millis();
	*sync->acces.starting = starting; // le millis de acces permet d'avoir le start
	value = *sync->acces.locked;
	pthread_mutex_unlock(sync->acces.instance);
	while (!value)
	{
		//soprintf("time : %ld\n", time);
		if (thsync_syncro(sync, get_millis() - starting))
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
