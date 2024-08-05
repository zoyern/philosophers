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

int	simul_take_fork(t_thread *thread)
{
	soprintf("%Cb59b28(%d)\t| (%C03dffc(%d)) : %Cd62d54(has taken a fork)\n", thread->loop->millis, thread->id);
	thread->need_fork = 0;
	return (1);
}

int	death_thread(t_thread *thread)
{
	if (!thread)
		return (0);
	thread->loop->stop = 1;
	soprintf("hey\n");
	if (!*thread->stop && check_death_one(thread->life_guard) && thread->nbr_loop)
		soprintf("%Cb59b28(%d)\t| (%C03dffc(%d)) : %CFF4500(died)\n", thread->loop->millis, thread->id);
	else
	{
		*thread->life_guard[thread->id] = 1;
		if (check_death_all(thread->life_guard))
			*thread->stop = 1;
		return (0);
	}
	*thread->stop = 1;
	*thread->life_guard[thread->id] = 1;
	soprintf("h----ey\n");
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