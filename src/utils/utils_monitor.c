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
#include <sotypes/soprintf.h>
#include <sotime/gears.h>

t_monitor	*init_monitor(t_solib *solib, int nbr_philo, char **times, int nbr_loop)
{
	t_monitor	*monitor;

	monitor = solib->malloc(solib, sizeof(t_monitor));
	monitor->printable = solib->malloc(solib, sizeof(pthread_mutex_t));
	monitor->stoped = solib->malloc(solib, sizeof(pthread_mutex_t));
	monitor->updating = solib->malloc(solib, sizeof(pthread_mutex_t));
	monitor->nbr_loop = nbr_loop;
	monitor->nbr_philo = nbr_philo;
	monitor->times = times;
	monitor->loop = soloop_init(solib);
	monitor->threads = NULL;
	monitor->current_loop = 0;
	pthread_mutex_init(monitor->printable, NULL);
	pthread_mutex_init(monitor->stoped, NULL);
	pthread_mutex_init(monitor->updating, NULL);
	pthread_mutex_lock(monitor->printable);
	pthread_mutex_lock(monitor->stoped);
	return (monitor);
}

int		callback_monitor(t_soloop *loop, t_monitor *monitor, long time)
{
	pthread_mutex_unlock(monitor->updating);
	if (!time)
	{
		soprintf("unlock\n");
		pthread_mutex_unlock(monitor->printable);
		pthread_mutex_unlock(monitor->stoped);
	}
	if (monitor->nbr_loop != -1 && monitor->current_loop == monitor->nbr_loop - 1)
		loop->stop = 1;
	else
		monitor->current_loop++;
	//soprintf("%d\n", time);
	pthread_mutex_lock(monitor->updating);
	return (0);
}

int monitor_update(t_monitor *monitor)
{
	long	current;
	long	start;
	int		passed;

	if (!monitor->loop || !monitor->loop->solib)
		return (1);
	sotime_restart_loop(monitor->loop, 1);
	start = -1;
	current = 1;
	passed = 0;
	while (!monitor->loop->stop)
	{
		passed = 0;
		if (current >= 1)
		{
			passed = 1;
			if (callback_monitor(monitor->loop, monitor, monitor->loop->millis))
				return (1);
			start = monitor->loop->millis;
		}
		current = monitor->loop->millis - start;
		updating_time(monitor->loop, passed);
	}
	return (0);
}
