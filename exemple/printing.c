/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:52:06 by marvin            #+#    #+#             */
/*   Updated: 2024/11/05 19:52:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exemple.h"

int	print_died(long time, int id)
{
	soprintf("%ld \t%d\tdied\n", time, id + 1);
	return (0);
}

int	routine(t_sothread *thread, t_philo *philo)
{
	if (sotask(thread->millis, philo->tasks[thread->id], thread))
		th_wait(thread, 0);
	if (philo->tasks[thread->id]->loop == philo->loop)
		return (1);
	return (0);
}

int	print_sleep_start(long time, t_sotask *task,
		t_philo *philo, t_sothread *thread)
{
	(void)time;
	(void)task;
	(void)philo;
	pthread_mutex_lock(thread->acces.instance);
	if (!*thread->acces.locked)
		soprintf("%ld \t%d\tis sleeping\n", time, thread->id + 1);
	pthread_mutex_unlock(thread->acces.instance);
	return (0);
}

int	print_eat_end(long time, t_sotask *task,
		t_philo *philo, t_sothread *thread)
{
	(void)time;
	(void)task;
	(void)philo;
	th_free(thread);
	return (0);
}

int	print_think_start(long time, t_sotask *task,
		t_philo *philo, t_sothread *thread)
{
	(void)time;
	(void)task;
	(void)philo;
	pthread_mutex_lock(thread->acces.instance);
	if (!*thread->acces.locked)
		soprintf("%ld \t%d\tis thinking\n", time, thread->id + 1);
	pthread_mutex_unlock(thread->acces.instance);
	return (0);
}
