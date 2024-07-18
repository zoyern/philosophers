/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 21:31:29 by marvin            #+#    #+#             */
/*   Updated: 2024/06/04 16:53:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers/all.h>
#include <stdio.h>

int	philo_print(t_soloop *loop, t_philo *philo, char *str, t_sotimer *starting)
{
	(void)str;
	pthread_mutex_lock(philo->death);
	if (*(philo->is_dead))
	{
		pthread_mutex_unlock(philo->death);
		loop->stop = 1;
		return (1);
	}
	pthread_mutex_unlock(philo->death);
	pthread_mutex_lock(philo->printable);
	loop->print("%d %C45ba4d(%d) %Ca7ba45(%s)\n", loop->millis, philo->id, str);
	pthread_mutex_unlock(philo->printable);
	if (starting)
		starting->start = 1;
	return (0);
}

int	my_update(t_soloop *loop, t_philo *philo, long time)
{
	if (philo->dying->finish)
	{
		pthread_mutex_lock(philo->death);
		pthread_mutex_lock(philo->printable);
		if (*(philo->is_dead))
		{
			pthread_mutex_unlock(philo->death);
			pthread_mutex_unlock(philo->printable);
			loop->stop = 1;
			return (0);
		}
		*philo->is_dead = 1;
		loop->print("%d %C#45ba4d(%d) %CFF0000(dying !)\n", time, philo->id);
		pthread_mutex_unlock(philo->death);
		pthread_mutex_unlock(philo->printable);
	}
	if (!time)
	{
		if (philo_print(loop, philo, "eat", philo->eat))
			return (0);
		philo->dying->start = 1;
	}
	if (philo->eat->finish)
		if (philo_print(loop, philo, "sleep", philo->sleep))
			return (0);
	if (philo->sleep->finish)
	{
		loop->timers->reset(loop, philo->dying, 1);
		if (philo_print(loop, philo, "eat", philo->eat))
			return (0);
	}
	return (0);
}

void	*philosopher_thread(void *arg)
{
	t_soloop	*loop;
	t_philo		*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->started);
	loop = philo->solib->time->loop(philo->solib);
	philo->eat = loop->timers->new(loop, 0, 200);
	philo->sleep = loop->timers->new(loop, 0, 200);
	philo->dying = loop->timers->new(loop, 0, 800);
	pthread_mutex_unlock(philo->started);
	philo->solib->time->start(loop, 1, philo, my_update);
	return (NULL);
}

t_monitor	*monitor_init(t_solib *solib, int nbr_philo)
{
	t_monitor	*monitor;
	int			i;

	monitor = solib->malloc(solib, sizeof(t_monitor));
	monitor->solib = solib;
	monitor->nbr_philo = nbr_philo;
	monitor->started = solib->malloc(solib, sizeof(pthread_mutex_t));
	monitor->printable = solib->malloc(solib, sizeof(pthread_mutex_t));
	monitor->death = solib->malloc(solib, sizeof(pthread_mutex_t));
	monitor->is_dead = solib->malloc(solib, sizeof(int));
	pthread_mutex_init(monitor->started, NULL);
	pthread_mutex_init(monitor->printable, NULL);
	pthread_mutex_init(monitor->death, NULL);
	pthread_mutex_lock(monitor->started);
	pthread_mutex_lock(monitor->printable);
	*monitor->is_dead = 0;
	monitor->philos = solib->malloc(solib, sizeof(t_philo *) * (nbr_philo + 1));
	i = 0;
	while (i < nbr_philo)
	{
		monitor->philos[i] = solib->malloc(solib, sizeof(t_philo));
		monitor->philos[i]->id = i;
		monitor->philos[i]->started = monitor->started;
		monitor->philos[i]->printable = monitor->printable;
		monitor->philos[i]->death = monitor->death;
		monitor->philos[i]->is_dead = monitor->is_dead;
		monitor->philos[i]->solib = solib;
		i++;
	}
	monitor->philos[i] = NULL;
	return (monitor);
}

int	philosophers(t_solib *solib, int nbr_philo)
{
	t_monitor	*monitor;
	int			i;

	monitor = monitor_init(solib, nbr_philo);
	i = 0;
	while (monitor->philos[i])
	{
		solib->print("init id : %d\n", monitor->philos[i]->id);
		pthread_create(&monitor->philos[i]->thread, NULL, philosopher_thread,
			monitor->philos[i]);
		i++;
	}
	solib->print("-- \t --\n");
	pthread_mutex_unlock(monitor->started);
	pthread_mutex_unlock(monitor->printable);
	i = 0;
	while (monitor->philos[i])
	{
		pthread_join(monitor->philos[i]->thread, NULL);
		i++;
	}
	return (0);
}
