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
	if (call_mutex(thread->stoped, mutex_get_int, thread->loop, NULL) || thread->times[0]->finish)
		return (0);
	soprintf("%Cb59b28(%d)\t| (%C03dffc(%d)) : %Cd62d54(has taken a fork)\n", thread->loop->millis, thread->id);
	return (0);
}

int	print_eating(t_thread *thread)
{
	if (call_mutex(thread->stoped, mutex_get_int, thread->loop, NULL) || thread->times[0]->finish)
		return (0);
	soprintf("%Cb59b28(%d)\t| (%C03dffc(%d)) : %Cd62d54(is eating)\n", thread->loop->millis, thread->id);
	thread->times[1]->start = 1;
	thread->times[0]->start = 1;
	return (0);
}

int	print_thinking(t_thread *thread)
{
	if (thread->nbr_loop && !*thread->stop)
		soprintf("%Cb59b28(%d)\t|  - %d -(%C03dffc(%d)) : %Cd62d54(is thinking)\n", thread->loop->millis, !*thread->stop, thread->id);
	thread->nbr_loop--;
	if (thread->nbr_loop)
		return (0);
	thread->times[0]->finish = 1;
	return (0);
}
int	print_sleeping(t_thread *thread)
{
	if (call_mutex(thread->stoped, mutex_get_int, thread->loop, NULL) && thread->times[0]->finish)
		return (0);
	soprintf("%Cb59b28(%d)\t| (%C03dffc(%d)) : %Cd62d54(is sleeping)\n", thread->loop->millis, thread->id);
	thread->times[2]->start = 1;
	return (0);
}
