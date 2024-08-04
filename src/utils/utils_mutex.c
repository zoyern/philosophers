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

int		mutex_get_stop(t_soloop *loop)
{
	return (loop->stop);
}

int		mutex_stop(t_thread *thread)
{
	soprintf("%d\t%CFF4500(THREAD %d IS DEAD !!)\n",thread->loop->millis, thread->id);
	thread->loop->stop = 1;
	return (0);
}

int		mutex_timer_finish(t_sotimer *timer)
{
	if (timer->finish)
		soprintf("%p%CFF4500(TIMER IS FINISH !!)\n",timer);
	return (0);
}