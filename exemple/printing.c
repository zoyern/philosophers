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

int	print_eat_start(long time, t_sotask *task, t_philo *philo, t_sothread *thread)
{
	(void)time;
	(void)task;
	(void)philo;
	pthread_mutex_lock(thread->acces.instance);
	soprintf("%ld \t%d\tis eating\n", time, thread->id + 1);
	pthread_mutex_unlock(thread->acces.instance);
	return (0);
}
int	print_sleep_start(long time, t_sotask *task, t_philo *philo, t_sothread *thread)
{
	(void)time;
	(void)task;
	(void)philo;
	pthread_mutex_lock(thread->acces.instance);
	soprintf("%ld \t%d\tis sleeping\n", time, thread->id + 1);
	pthread_mutex_unlock(thread->acces.instance);
	return (0);
}


int	print_eat_end(long time, t_sotask *task, t_philo *philo, t_sothread *thread)
{
	(void)time;
	(void)task;
	(void)philo;
	th_free(thread);
	return (0);
}

int	print_think_start(long time, t_sotask *task, t_philo *philo, t_sothread *thread)
{
	(void)time;
	(void)task;
	(void)philo;
	pthread_mutex_lock(thread->acces.instance);
	soprintf("%ld \t%d\tis thinking\n", time, thread->id + 1);
	pthread_mutex_unlock(thread->acces.instance);
	return (0);
}
