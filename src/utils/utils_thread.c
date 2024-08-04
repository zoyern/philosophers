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
	while (i < monitor->nbr_philo)
	{
		threads[i] = solib->malloc(solib, sizeof(t_thread));
		threads[i]->id = i;
		threads[i]->monitor = monitor;
		threads[i]->loop = soloop_init(solib);
		threads[i]->times = create_timers(solib, threads[i]->loop, monitor->times);
		threads[i]->printable = monitor->printable;
		threads[i]->stoped = monitor->stoped;
		threads[i]->updating = monitor->updating;
		pthread_create(&threads[i]->instance, NULL, thread_update, threads[i]);
		pthread_detach(threads[i]->instance);
		i++;
	}
	return (threads);
}
//mutex_timer_finish

int		callback_thread(t_soloop *loop, t_monitor *monitor, long time)
{

	return (0);
}

void	*thread_update(void *arg)
{
	t_thread	*thread;

	thread = (t_thread *)arg;
	//call_mutex(thread->printable, print_init_thread, thread);
	long	current;
	long	start;
	int		passed;

	if (!thread->loop || !thread->loop->solib)
		return (1);
	sotime_restart_loop(thread->loop, 1);
	start = -1;
	current = 1;
	passed = 0;
	while (!thread->loop->stop)
	{
		passed = 0;
		if (current >= 1)
		{
			passed = 1;
			if (callback_thread(thread->loop, thread, thread->loop->millis))
				return (1);
			start = thread->loop->millis;
		}
		current = thread->loop->millis - start;
		updating_time(thread->loop, passed);
	}
	/*while (!call_mutex(thread->stoped, mutex_get_stop, thread->loop))
	{
		// PROBLEMME AVEC MA LIB NECESSITE UN MUTEX POUR CHECK SI FINISH EST DISPONIBLE DONC QUE 
		// sotime_update_timer ai été executé correctement 
		call_mutex(thread->updating, mutex_timer_finish, thread->times[1]);
		call_mutex(thread->updating, mutex_timer_finish, thread->times[0]);
	}*/
	return (NULL);
}
