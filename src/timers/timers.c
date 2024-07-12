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


t_sotimer	*timer_list_add(t_solib *solib, int start, long millis)
{
	t_sotimer	*timer;

	timer = solib->malloc(solib, sizeof(t_sotimer));
	timer->start = start;
	timer->millis = 0;
	timer->start_millis = 0;
	timer->working = 0;
	timer->finish = 0;
	timer->time = millis;
	timer->next = solib->time->timers->first;
	solib->time->timers->first = timer;
	return (timer);
}

void	timer_reset(t_sotimer *timer, int start)
{
	timer->start = start;
	timer->millis = 0;
	timer->start_millis = 0;
	timer->working = 0;
	timer->finish = 0;
}

void	timer_list_clear(t_solib *solib)
{
	t_sotimer	*box;
	t_sotimer	*tmp;

	if (!solib->time || !solib->time->timers)
		return ;
	box = solib->time->timers->first;
	while (box)
	{
		tmp = box->next;
		solib->free(solib, box);
		box = tmp;
	}
	solib->free(solib, solib->time->timers);
	solib->time->timers = NULL;
}

void	sonew_timers_list(t_solib *solib)
{
	if (!solib)
		return ;
	if (solib->time->timers)
		timer_list_clear(solib);
	solib->time->timers = solib->malloc(solib, sizeof(t_sotimers_list));
	solib->time->timers->first = solib->malloc(solib, sizeof(t_sotimer));
	solib->time->timers->first->next = NULL;
	solib->time->timers->add = timer_list_add;
	solib->time->timers->reset = timer_reset;
	solib->time->timers->clear = timer_list_clear;
}
