/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sotask_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:52:05 by marvin            #+#    #+#             */
/*   Updated: 2024/10/21 14:52:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <sothread/all.h>
# include <solibft/sostdlib.h>


t_sotask	*sonew_task(t_solib *solib, char *time, int (*callback)(), void *data)
{
	t_sotask	*task;

	task = somalloc(solib, sizeof(t_sotask));
	task->id = 0;
	task->time = ft_atoi(time);
	task->start = 0;
	task->work = 0;
	task->end = 0;
	task->callback = callback;
	task->data = data;
	task->next = NULL;
	return (task);
}

t_sotasks	*sonew_tasklist(t_solib *solib)
{
	t_sotasks	*list;

	list = somalloc(solib, sizeof(t_sotasks));
	list->loop = 0;
	list->count = 0;
	list->starting = 0;
	list->current = NULL;
	list->first = NULL;
	return (list);
}

void	add_task(t_sotasks *list, unsigned long id, t_sotask *task)
{
	t_sotask	*current;

	if (!task || !list)
		return ;
	current = list->current;
	if (!current)
		return ((void)(task->id = id, task->start = 1 ,
			list->count++, list->current = task, list->first = task));
	while (current->next)
		current = current->next;
	task->id = id;
	list->count++;
	current->next = task;
}

void	change_task_state(t_sotask *sotask, int start, int work, int end)
{
	if (!sotask)
		return ;
	sotask->start = start;
	sotask->work = work;
	sotask->end = end;
}

void task_start(long time, t_sotasks *tasks, void *data)
{
	tasks->starting = time;
	if (tasks->current->callback)
		tasks->current->callback(time, tasks->current, tasks->current->data, data);
	change_task_state(tasks->current, 0, 1, 0);
}

void task_work(long time, t_sotasks *tasks, void *data)
{
	if (tasks->current->callback)
		tasks->current->callback(time, tasks->current, tasks->current->data, data);
	if (tasks->starting - time >= tasks->current->time)
		change_task_state(tasks->current, 0, 0, 1);
}

int task_end(long time, t_sotasks *tasks, void *data)
{
	t_sotask	*task;
	if (tasks->current->callback)
		tasks->current->callback(time, tasks->current, tasks->current->data, data);
	task = tasks->current->next;
	if (task)
	{
		tasks->current = task;
		tasks->starting = time;
		change_task_state(tasks->current, 0, 1, 0);
		return (0);
	}
	tasks->loop++;
	tasks->current = tasks->first;
	change_task_state(tasks->current, 1, 0, 0);
	return (1);
}

int	sotask(long time, t_sotasks *tasks, void *data)
{
	if (!tasks || !tasks->current)
		return (1);
	if (tasks->current->start)
		task_start(time, tasks, data);
	if (tasks->current->work)
		task_work(time, tasks, data);
	if (tasks->current->end)
		return (task_end(time, tasks, data));
	return (0);
}