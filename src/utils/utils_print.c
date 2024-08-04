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

int		print_init_thread(t_thread *thread)
{
	soprintf("id : %d\n---------\n", thread->id);
	int	i = 0;
	while (thread->times[i])
	{
		soprintf("%p | time %d : %d\n",thread->times[i],  i, thread->times[i]->time);
		i++;
	}
	soprintf("---------\n");
	return (0);
}

int		print_time_eating(t_thread *thread)
{
	soprintf("%d | time %d : eating -- %d %d %d\n",thread->id,  thread->times[1]->millis,
			thread->times[1]->start, thread->times[1]->working, thread->times[1]->finish);
	soprintf("---------\n");
	return (0);
}

int		print_eating(t_thread *thread)
{
	soprintf("%d | time %d : finished eating\n",thread->id,  thread->loop->millis);
	soprintf("---------\n");
	return (0);
}