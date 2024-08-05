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
#include <sotypes/soprintf.h>

int	philosophers(t_solib *solib, int nbr_philo, char **times, int nbr_loop)
{
	t_monitor	*monitor;

	solib->print("%d %d\n%S-------------------------\n\n",nbr_philo, nbr_loop, times);
	monitor = init_monitor(solib, nbr_philo, times, nbr_loop);
	monitor->threads = init_thread(solib, monitor);
	monitor_update(monitor);
	soprintf("%Cb59b28(%d)\t| (%C03dffc(MONITOR))\t\t\t: %CFF0000(philosophers has been terminated !)\n", monitor->loop->millis);
	return (0);
} 