/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 01:30:02 by marvin            #+#    #+#             */
/*   Updated: 2024/08/02 01:30:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers/all.h>
#include <sotime/gears.h>
#include <solibft/sostdlib.h>

t_monitor	*init_monitor(t_solib *solib, int nbr_philo, char **times, int nbr_loop)
{
	t_monitor	*monitor;
	int			i;

	monitor = solib->malloc(solib, sizeof(t_monitor));
	monitor->printable = solib->malloc(solib, sizeof(pthread_mutex_t));
	monitor->stoped = solib->malloc(solib, sizeof(pthread_mutex_t));
	monitor->take = solib->malloc(solib, sizeof(pthread_mutex_t));
	monitor->life_guard = solib->malloc(solib, sizeof(int *) * (nbr_philo + 1));
	monitor->acces = solib->malloc(solib, sizeof(int *) * (nbr_philo + 1));
	i = 0;
	while (i < nbr_philo)
	{
		monitor->life_guard[i] = solib->malloc(solib, sizeof(int));
		*monitor->life_guard[i] = 0;
		monitor->acces[i] = solib->malloc(solib, sizeof(int));
		*monitor->acces[i] = 1;
		i++;
	}
	monitor->life_guard[i] = NULL;
	monitor->acces[i] = NULL;
	monitor->stop = solib->malloc(solib, sizeof(int));
	*monitor->stop = 0;
	monitor->stape = solib->malloc(solib, sizeof(int));
	*monitor->stape = 0;
	monitor->nbr_loop = nbr_loop;
	monitor->nbr_philo = nbr_philo;
	monitor->times = times;
	monitor->loop = soloop_init(solib);
	monitor->threads = NULL;
	monitor->current_loop = 0;
	pthread_mutex_init(monitor->printable, NULL);
	pthread_mutex_init(monitor->stoped, NULL);
	pthread_mutex_init(monitor->take, NULL);
	pthread_mutex_lock(monitor->printable);
	pthread_mutex_lock(monitor->stoped);
	return (monitor);
}

int		callback_monitor(t_monitor *monitor, long time)
{
	if (!time)
	{
		pthread_mutex_unlock(monitor->printable);
		pthread_mutex_unlock(monitor->stoped);
	}
	if (call_mutex(monitor->stoped, mutex_get_int, monitor->stop, NULL))
		call_mutex(monitor->printable, call_death, NULL, monitor);
	//if (monitor->nbr_philo > 0)

	return (0);
}

int monitor_update(t_monitor *monitor)
{
	long	current;
	long	start;
	int		passed;

	if (!monitor->loop || !monitor->loop->solib)
		return (1);
	start = -monitor->loop->millis_update;
	current = monitor->loop->millis_update;
	passed = 0;
	while (!monitor->loop->stop)
	{
		passed = 0;
		if (current >= monitor->loop->millis_update)
		{
			passed = 1;
			if (callback_monitor(monitor, monitor->loop->millis))
				return (1);
			start = monitor->loop->millis;
		}
		current = monitor->loop->millis - start;
		updating_time(monitor->loop, passed);
	}
	return (0);
}
