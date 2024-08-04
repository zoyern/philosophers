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

#include <philosophers/all.h>
#include <solibft/sostdlib.h>

int	simul_take_fork(t_thread *thread)
{
	soprintf("%Cb59b28(%d)\t| (%C03dffc(%d)) : %Cd62d54(has taken a fork)\n", thread->loop->millis, thread->id);
	thread->need_fork = 0;
	return (1);
}

int	print_fork(t_thread *thread)
{
	if (call_mutex(thread->stoped, mutex_get_int, thread->loop, NULL) || thread->times[0]->finish)
		return (0);
	if (!thread->need_fork)
		thread->need_fork = 1;
	if (simul_take_fork(thread))
		print_eating(thread);
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
	if (call_mutex(thread->stoped, mutex_get_int, thread->loop, NULL) || thread->times[0]->finish)
		return (0);
	soprintf("%Cb59b28(%d)\t| (%C03dffc(%d)) : %Cd62d54(is thinking)\n", thread->loop->millis, thread->id);
	thread->nbr_loop--;
	if (!thread->nbr_loop)
		thread->loop->stop = 1;
	else
	{
		print_fork(thread);
		
	}
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
