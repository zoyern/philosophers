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
#include <sotime/gears.h>
#include <sotime/timers.h>

t_thread	**init_thread(t_solib *solib, t_monitor *monitor)
{
	t_thread		**threads;
	int	i;

	i = 0;
	threads = solib->malloc(solib, sizeof(t_thread *) * (monitor->nbr_philo + 1));
	threads[monitor->nbr_philo] = NULL;
	sotime_restart_loop(monitor->loop, 1);
	while (i < monitor->nbr_philo)
	{
		threads[i] = solib->malloc(solib, sizeof(t_thread));
		threads[i]->id = i;
		threads[i]->monitor = monitor;
		threads[i]->loop = soloop_init(solib);
		threads[i]->loop->starting_time = monitor->loop->starting_time;
		threads[i]->loop->current = monitor->loop->current;
		threads[i]->loop->millis_update = monitor->loop->millis_update;
		threads[i]->stop = monitor->stop;
		threads[i]->stape = monitor->stape;
		threads[i]->nbr_loop = monitor->nbr_loop;
		threads[i]->need_fork = 0;
		threads[i]->nbr_philo = monitor->nbr_philo;
		threads[i]->life_guard = monitor->life_guard;
		threads[i]->acces = monitor->acces;
		threads[i]->times = create_timers(solib, threads[i]->loop, monitor->times);
		threads[i]->times[0]->start = 1;
		threads[i]->printable = monitor->printable;
		threads[i]->stoped = monitor->stoped;
		threads[i]->take = monitor->take;
		pthread_create(&threads[i]->instance, NULL, thread_update, threads[i]);
		pthread_detach(threads[i]->instance);
		i++;
	}
	return (threads);
}

int		callback_thread(t_thread *thread)
{
	if (thread->times[1]->finish)
		call_mutex(thread->printable, print_sleeping, thread, NULL);
	if (call_mutex(thread->printable, mutex_get_fork, thread, NULL))
		call_mutex(thread->printable, print_eating, thread, NULL);
	if (thread->times[2]->finish)
		call_mutex(thread->printable, print_thinking, thread, NULL);
	if (thread->times[1]->finish)
		call_mutex(thread->printable, print_sleeping, thread, NULL);
	if (thread->times[0]->finish)
		call_mutex(thread->printable, call_death, thread, NULL);
	return (0);
}

void	*thread_update(void *arg)
{
	t_thread	*thread;

	thread = (t_thread *)arg;
	if (!thread->loop || !thread->loop->solib)
		return (NULL);
	while (!thread->loop->stop || !call_mutex(thread->stoped, mutex_get_int, thread->stop, NULL))
	{
		if (callback_thread(thread))
			return (NULL);
		updating_time(thread->loop, 1);
	}
	return (NULL);
}
