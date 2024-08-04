/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 01:30:31 by marvin            #+#    #+#             */
/*   Updated: 2024/08/02 01:30:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers/all.h>
#include <sotypes/soprintf.h>

int		mutex_get_int(int *value)
{
	return (*value);
}

int	death_thread(t_thread *thread)
{
	if (!thread)
		return (0);
	if (!*thread->stop && !thread->loop->stop)
		soprintf("%Cb59b28(%d)\t| (%C03dffc(%d)) : %CFF4500(died)\n", thread->loop->millis, thread->id);
	*thread->stop = 1;
	thread->loop->stop = 1;
	return (0);
}

int	death_monitor(t_monitor *monitor)
{
	if (!monitor)
		return (0);
	if (*monitor->stop)
		monitor->loop->stop = 1;
	if (monitor->loop->stop)
		*monitor->stop = 1;
	return (0);
}

int	call_death(t_thread *thread, t_monitor *monitor)
{
	death_thread(thread);
	death_monitor(monitor);
	return (0);
}