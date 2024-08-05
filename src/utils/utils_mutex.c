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

int		mutex_get_int(int *value)
{
	return (*value);
}

int	mutex_set_fork(t_thread *thread, int **value)
{
	*value[thread->id] = 1;
	*value[(thread->id + 1) % thread->nbr_philo] = 1;
	thread->need_fork = 0;
	return (0);
}

int	update_stape(t_thread *thread)
{
	*thread->stape = (*thread->stape + 1) % thread->nbr_philo;
	return (0);
}

int	mutex_get_fork(t_thread *thread)
{
	if (!*thread->acces[thread->id])
		return (update_stape(thread));
	if (!thread->acces[(thread->id + 1) % thread->nbr_philo] || !*thread->acces[(thread->id + 1) % thread->nbr_philo])
		return (update_stape(thread));
	*thread->acces[(thread->id + 1) % thread->nbr_philo] = 0;
	call_mutex(thread->printable, print_fork, thread, NULL);
	if (!thread->acces[thread->id] || !*thread->acces[thread->id])
		return (update_stape(thread));
	*thread->acces[thread->id] = 0;
	call_mutex(thread->printable, print_fork, thread, NULL);
	update_stape(thread);
	return (1);
}

int	death_thread(t_thread *thread)
{
	if (!thread)
		return (0);
	thread->loop->stop = 1;
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