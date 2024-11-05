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


// creation du monitor sync combien de thread il va géré avec la syncronisation (pour philosopher 2 mais peu etre 1, 4, 10 etc)
t_sothsync	*sothsync(t_solib *solib, int nbr, int syncro)
{
	t_sothsync	*sync;

	sync = somalloc(solib, sizeof(t_sothsync));
	sync->threads = somalloc(solib, sizeof(t_sothread *) * (nbr + 1));
	sync->forks = new_mutexs(solib, nbr, 0, 0);
	sync->threads[nbr] = NULL;
	sync->print = new_mutex(solib, 0, 0);
	sync->acces = new_mutex(solib, 0, 0);
	sync->thread_acces = new_mutex(solib, 0, 0);
	sync->starting = somalloc(NULL, sizeof(long));
	sync->value = somalloc(NULL, sizeof(int));
	sync->solib = solib;
	sync->nbr = nbr;
	sync->syncro = syncro;
	*sync->value = 0;
	*sync->starting = get_millis();
	pthread_mutex_lock(sync->acces.acces);
	pthread_mutex_lock(sync->thread_acces.acces);
	if (pthread_create(&sync->instance, NULL, sothsync_routine, sync))
       	return (solib->close(solib, 1), NULL);
    pthread_detach(sync->instance);
	return (sync);
}

void* sothsync_routine(void* arg)
{
    t_sothsync *sync = (t_sothsync *)arg;  // Cast de l'argument en entier
	int		value;

	mutex(sync->acces, NULL, NULL);
	*sync->starting = get_millis();
	pthread_mutex_unlock(sync->thread_acces.acces);
	value = 0;
	while (!value)
	{
		sync_threads(sync->nbr, sync);
		pthread_mutex_lock(sync->acces.acces);
		value = *sync->value;
		pthread_mutex_unlock(sync->acces.acces);
	}
    return (NULL);
}

void	sync_threads(int nbr, t_sothsync *sync)
{
	int	i;
	int	j;

	i = -1;
	while (++i < nbr) // id de ma fork 
	{
		j = -1;
		while (++j < nbr) // id de ma fork 
			reset_fork(j, sync->syncro, sync->nbr, sync->forks);
		if (!check_eat(i,  sync->syncro, sync->nbr, sync->forks) && get_fork(i, sync->syncro, sync->nbr, sync->forks))
		{
			pthread_mutex_lock(sync->forks[i].acces);
			pthread_mutex_lock(sync->print.acces);
			soprintf("%ld \t%d\thas taken a fork\n", get_millis() - *sync->starting , i  + 1);
			soprintf("%ld \t%d\thas taken a fork\n", get_millis() - *sync->starting , i  + 1);
			*sync->forks[i].value = 1;
			*sync->forks[i].eat += 1;
			*sync->forks[i].time = get_millis();
			pthread_mutex_unlock(sync->forks[i].acces);
			pthread_mutex_unlock(sync->print.acces);
		}
	}
}

int	sothpause(t_sothread *thread, int value, int finish)
{
	pthread_mutex_lock(thread->fork.acces);
	*thread->fork.value = value;
	*thread->fork.finish = finish;
	*thread->fork.locked = 0;
	pthread_mutex_unlock(thread->fork.acces);
	return (0);
}