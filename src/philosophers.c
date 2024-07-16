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

typedef struct s_philo
{
	int			*started;
	int			id;
	pthread_t	thread;
}	t_philo;

typedef struct s_monitor
{
	int		*started;
	t_solib	*solib;
	int		nbr_philo;
	t_philo	**philos;
}	t_monitor;

void	*philosopher_thread(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	printf("Philosopher %d started : fork [%d][%d]\n", philo->id, philo->left_fork->id, philo->right_fork->id);
	return (NULL);
}

t_monitor	*monitor_init(t_solib *solib, int nbr_philo)
{
	t_monitor	*monitor;
	int			i;

	monitor = solib->malloc(solib, sizeof(t_monitor));
	monitor->solib = solib;
	monitor->nbr_philo = nbr_philo;
	monitor->started = solib->malloc(solib, sizeof(int));
	*monitor->started = 0;
	monitor->philos = solib->malloc(solib, sizeof(t_philo *) * (nbr_philo + 1));
	i = 0;
	while (i < nbr_philo)
	{
		monitor->philos[i] = solib->malloc(solib, sizeof(t_philo));
		monitor->philos[i]->id = i;
		monitor->philos[i]->started = monitor->started;
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
		solib->print("started %d -- id : %d\n", *monitor->philos[i]->started, monitor->philos[i]->id);
		i++;
	}
	*monitor->started = 1;
	i = 0;
	solib->print("-- \t --\n");
	while (monitor->philos[i])
	{
		solib->print("started %d -- id : %d\n", *monitor->philos[i]->started, monitor->philos[i]->id);
		i++;
	}
	return (0);
}

/*int	philosophers(t_solib *solib, int nbr_philo)
{
	t_thread_data	data;
	int				i;

	(void)solib;
	data.philosophers = malloc(nbr_philo * sizeof(t_philosopher));
	data.forks = malloc(nbr_philo * sizeof(t_fork));
	data.num_philosophers = nbr_philo;
	data.threads = malloc(nbr_philo * sizeof(pthread_t));
	i = 0;
	while (i < nbr_philo)
	{
		data.philosophers[i].id = i;
		data.philosophers[i].left_fork = &data.forks[i];
		data.philosophers[i].right_fork = &data.forks[(i + 1) % nbr_philo];
		pthread_mutex_init(&data.forks[i].mutex, NULL);
		i++;
	}
	i = 0;
	while (i < nbr_philo)
	{
		pthread_create(&data.threads[i], NULL, philosopher_thread,
			&data.philosophers[i]);
		i++;
	}
	i = 0;
	while (i < nbr_philo)
	{
		pthread_join(data.threads[i], NULL);
		i++;
	}
	free(data.philosophers);
	free(data.forks);
	free(data.threads);
	return (0);
}*/
