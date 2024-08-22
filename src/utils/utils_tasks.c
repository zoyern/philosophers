/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tasks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 05:36:45 by marvin            #+#    #+#             */
/*   Updated: 2024/08/20 05:36:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers/all.h>

t_sotimer	**create_timers(t_solib *solib, t_soloop *loop, char **strs)
{
	t_sotimer	**timers;
	int			i;	

	i = 0;
	while (strs[i])
		i++;
	timers = solib->malloc(solib, sizeof(t_sotimer *) * (i + 1));
	i = 0;
	while (strs[i])
	{
		timers[i] = loop->timers->new(loop, 0, ft_atoi(strs[i]));
		i++;
	}
	timers[i] = NULL;
	return (timers);
}


int	tasks_create(t_monitorb *monitor, t_threadb *thread)
{
	monitor.
	return (0);
}

int	tasks_clear(t_monitorb *monitor, t_threadb *thread)
{
	return (0);
}

int	tasks_check(t_monitorb *monitor, int *task)
{
	if (monitor->stop)
		return (0);
	return (*task);
}

//simulation
int	start_task(t_threadb *thread, int **task, int id)
{
	if (!task[id])
		id = 0;
	if (!id) //task 0 check fork
		return (check_fork());
	*task[id][0] = 0;
	*task[id][1] = 1;
	*task[id][2] = thread->monitor->millis + *task[id][3];
}

int	tasks_next(t_threadb *thread, int *task)
{
	int	**tasks;
	int	i;

	if (monitor->stop)
		return (0);
	tasks = thread->monitor->tasks[thread->id];
	i = -1;
	while (tasks[++i])
	{
		if (*tasks[i][0]) // si j'ai trouver la task fini je dois commencer l'autre
		{
			start_task(thread, tasks, i + 1);
		}
	}
	*task = 0;
	return (0);
}