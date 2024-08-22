/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 21:33:45 by marvin            #+#    #+#             */
/*   Updated: 2024/08/05 21:33:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers/all.h>
#include <solibft/sostdlib.h>

int	print_fork(t_thread *thread)
{
	if (call_mutex(thread->stoped, mutex_get_int, thread->loop, NULL))
		return (0);
	soprintf("%Cb59b28(%d)\t| (%C03dffc(%d)) : %Cd62d54(has taken a fork)\n", thread->loop->millis, thread->id);
	return (0);
}

int	print_eating(t_thread *thread)
{
	if (call_mutex(thread->stoped, mutex_get_int, thread->loop, NULL))
		return (0);
	soprintf("%Cb59b28(%d)\t| (%C03dffc(%d)) : %Cd62d54(is eating)\n", thread->loop->millis, thread->id);
	thread->loop->reset(thread->loop, thread->times[1]);
	thread->loop->reset(thread->loop, thread->times[0]);
	return (0);
}

int	print_thinking(t_thread *thread)
{
	if (thread->nbr_loop || *thread->stop)
		soprintf("%Cb59b28(%d)\t|  (%C03dffc(%d)) : %Cd62d54(is thinking)\n", thread->loop->millis, thread->id);
	thread->nbr_loop--;
	if (thread->nbr_loop)
		return (0);
	thread->times[0]->finish = 1;
	return (0);
}
int	print_sleeping(t_thread *thread)
{
	mutex_set_fork(thread, thread->acces);
	thread->times[2]->start = 1;
	return (0);
}
