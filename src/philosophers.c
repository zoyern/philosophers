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

void	*philosopher_thread(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	printf("Philosopher %d started\n", philo->id);
	return (NULL);
}

int	philosophers(t_solib *solib, int nbr_philo)
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
}
