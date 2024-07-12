/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:08:01 by marvin            #+#    #+#             */
/*   Updated: 2024/06/05 18:08:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sotime/all.h>
#include <stdio.h>


void	updating_time(t_solib *solib, int passed)
{
	t_sotimer	*box;

	solib->time->current = sotime_get_millis();
	solib->time->millis = solib->time->current - solib->time->starting_time;
	box = solib->time->timers->first;
	while (box->next)
	{
		sotime_update_timer(solib, box, passed);
		box = box->next;
	}
}


void	sotime_update_timer(t_solib *solib, t_sotimer *timer, int passed)
{
	if (!timer)
		return ;
	if (timer->start)
	{
		timer->start_millis = solib->time->get_millis();
		timer->millis = 0;
		timer->working = 1;
		timer->start = 0;
	}
	if (timer->finish && passed)
		timer->finish = 0;
	if (timer->working && !timer->start && timer->millis >= timer->time)
	{
		timer->working = 0;
		timer->finish = 1;
	}
	timer->millis = solib->time->get_millis() - timer->start_millis;
}

int	sotime_loop(t_solib *solib, long millis, void *data, int (*callback)())
{
	long	current;
	long	start;
	int		passed;

	if (!solib || !solib->time)
		return (1);
	solib->time->stop = 0;
	solib->time->starting_time = sotime_get_millis();
	start = -millis;
	current = 0;
	passed = 0;
	while (!solib->time->stop)
	{
		updating_time(solib, passed);
		passed = 0;
		if (current >= millis)
		{
			passed = 1;
			if (callback)
				if (callback(solib, data, solib->time->millis))
					return (1);
			start = solib->time->millis;
		}
		current = solib->time->millis - start;
	}
	return (0);
}

long	sotime_get_millis()
{
    struct timeval	time;

    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000) + (time.tv_usec / 1000);
}

t_sotimer	sotime_timer_init(int start)
{
	t_sotimer	timer;

	timer.start = start;
	timer.millis = 0;
	timer.start_millis = 0;
	timer.working = 0;
	timer.finish = 0;
	return (timer);
}
