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
	//sotime_loop(loop, 1, monitor, monitor_update);
	//soprintf("%CFF0000(FINISH !!!!! )\n");
	return (0);
} 