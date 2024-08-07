/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 21:31:29 by marvin            #+#    #+#             */
/*   Updated: 2024/06/04 16:53:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers/all.h>
#include <sotime/gears.h>
#include <solibft/sostdlib.h>

typedef struct s_thread2	t_thread2;
typedef struct s_monitor2	t_monitor2;

typedef struct s_thread2
{
	int				id;
	int				*live;
	int				*fork;
	int				*loop;
	long			**times;
	long			*millis;
	void			*data;
	pthread_t		instance;
	pthread_mutex_t	*mutex;
	int 			(*call)();
	t_monitor2		*monitor;
}	t_thread2;

typedef struct s_monitor2
{
	t_thread2		**threads;
	int				**life_guard;
	int				**forks;
	int				**loops;
	long			***times;
	long			*millis;
	void			*data;
	long			starting;
	long			nbr;
	long			last_time;
	long			current;
	int				(*call)();
	pthread_mutex_t	*mutex;
}	t_monitor2;


int		mutex(pthread_mutex_t *mutex, int (*callback)(), void *var, void *value)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(mutex);
	if (callback)
		ret = callback(var, value);
	pthread_mutex_unlock(mutex);
	return (ret);
}


long	**format_times(t_solib *solib, char **strs)
{
	long	**timers;
	long	i;	

	i = 0;
	while (strs[i])
		i++;
	timers = somalloc(solib, sizeof(long *) * (i + 1));
	i = 0;
	while (strs[i])
	{
		timers[i] = somalloc(solib, sizeof(long) * 4);
		timers[i][0] = 0;
		timers[i][1] = ft_atoi(strs[i]);
		timers[i][2] = 0;
		timers[i][3] = 0;
		i++;
	}
	timers[i] = NULL;
	return (timers);
}

int	update_thread_times(t_thread2 *thread)
{
	int	i;

	i = 0;
	if (!thread || !thread->times)
		return (0);
	while (thread->times[i])
	{
		if (thread->times[i][4] && thread->times[i][1] >= thread->times[i][2] - *thread->millis)
		{
			thread->times[i][0] = 1;
			thread->times[i][4] = 0;
		}
		i++;
	}
	return (0);
}

int	update_time(t_monitor2 *monitor, t_thread2 *thread)
{
	long	deleyed;
	int		i;
 
	*monitor->millis = monitor->starting - sotime_get_millis();
	deleyed = *monitor->millis - monitor->last_time;
	if (deleyed > 1)
	{
		*monitor->millis -= deleyed - 1;
		monitor->starting += deleyed - 1;
	}
	monitor->last_time = *monitor->millis;
	if (thread)
		return (update_thread_times(thread));
	i = -1;
	while (monitor->threads[++i])
		update_thread_times(monitor->threads[i]);
	return (0);
}

t_thread2	*init_threads(t_solib *solib, int id, char **times, t_monitor2 *monitor)
{
	t_thread2	*thread;

	if (!monitor)
		return (NULL);
	thread = somalloc(solib, sizeof(t_thread2));
	thread->monitor = monitor;
	thread->id = id;
	monitor->forks[id] = somalloc(solib, sizeof(int));
	thread->fork = monitor->forks[id];
	*thread->fork = 1;
	monitor->life_guard[id] = somalloc(solib, sizeof(int));
	thread->live = monitor->life_guard[id];
	*thread->live = 1;
	thread->loop = monitor->life_guard[id];
	*thread->live = 1;
	thread->millis = monitor->millis;
	thread->loop = monitor->loops[id];
	thread->monitor = monitor;
	thread->mutex = monitor->mutex;
	monitor->times[id] = format_times(solib, times);
	thread->times = monitor->times[id];
	return (thread);
}

t_monitor2	*sothreads(t_solib *solib, int nbr, char **times, int loop)
{
	t_monitor2	*monitor;
	int			i;

	
	monitor = somalloc(solib, sizeof(t_monitor2));
	monitor->mutex = somalloc(solib, sizeof(pthread_mutex_t));
	monitor->threads = somalloc(solib, sizeof(t_thread2) * (nbr + 1));
	monitor->threads[nbr] = NULL;
	monitor->forks = somalloc(solib, sizeof(int *) * (nbr + 1));
	monitor->forks[nbr] = NULL;
	monitor->life_guard = somalloc(solib, sizeof(int *) * (nbr + 1));
	monitor->life_guard[nbr] = NULL;
	monitor->loops = somalloc(solib, sizeof(int *) * (nbr + 1));
	monitor->loops[nbr] = NULL;
	monitor->times = somalloc(solib, sizeof(long **) * (nbr + 1));
	monitor->times[nbr] = NULL;
	monitor->millis = somalloc(solib, sizeof(long));
	*monitor->millis = 0;
	monitor->nbr = nbr;
	pthread_mutex_init(monitor->mutex, NULL);
	pthread_mutex_lock(monitor->mutex);
	i = -1;
	while (++i < nbr)
	{
		monitor->loops[i] = somalloc(solib, sizeof(int));
		*monitor->loops[i] = loop;
		monitor->threads[i] = init_threads(solib, i, times, monitor);
		if (!monitor->threads[i])	
			return (NULL);
	}
	//soprintf("hey\n");
	return (monitor);
}

int	print_test(t_thread2 *thread)
{
	soprintf("%Cb59b28(%d)\t| (%C03dffc(%d)) : %Cd62d54(hey)\n",*thread->millis, thread->id);
	return (0);
}

int	get_int(int *value)
{
	return (*value);
}

int	thread_update_test(t_thread2 *thread, t_solib *solib)
{
	if (thread->times[1][0])
	{
		thread->times[1][0] = 0;
		mutex(thread->mutex, print_test, thread, NULL);
	}
	(void)thread;
	(void)solib;
	return (0);
}

int	monitor_update_test(t_monitor2 monitor, t_solib solib)
{
	(void)monitor;
	(void)solib;
	return (0);
}

int	reset_times(t_thread2 *thread, int id)
{
	update_time(thread->monitor, thread);
	thread->times[id][0] = 0;
	thread->times[id][2] = *thread->millis;
	thread->times[id][3] = 1;
	return (0);

}

void	*call_thread(void *arg)
{
	t_thread2	*thread;

	thread = (t_thread2 *)arg;
	
	mutex(thread->mutex, reset_times, thread, 0);
	while (1)
	{
		mutex(thread->mutex, update_time, thread->monitor, thread);
		if (thread->call)
			thread->call(thread, thread->data);
	}
	return (NULL);
}

void	take_fork(t_thread2 *thread1, t_thread2 *thread2)
{
	*thread1->fork = 0;
	thread1->times[0][0] = 0;
	thread1->times[0][3] = *thread1->millis;
	thread1->times[1][0] = 0;
	thread1->times[1][3] = *thread1->millis;
	*thread2->fork = 0;
	thread2->times[0][0] = 0;
	thread2->times[0][3] = *thread2->millis;
	thread2->times[1][0] = 0;
	thread2->times[1][3] = *thread2->millis;
}

int	call_fork(t_monitor2 *monitor)
{
	int	i;

	update_time(monitor, NULL);
	i = -1;
	while (monitor->threads[++i])
	{
		if (*monitor->threads[i]->fork && *monitor->threads[(i + 1) % monitor->nbr]->fork)
			take_fork(monitor->threads[i], monitor->threads[(i + 1) % monitor->nbr]);
	}
	return (0);
}

int	call_monitor(t_monitor2 *monitor)
{
	//verifie la mort et verifie si le thread peux travailler 
	monitor->last_time = 0;
	monitor->starting = sotime_get_millis();
	update_time(monitor, NULL);
	pthread_mutex_unlock(monitor->mutex);
	while (1)
	{
		//check fork
		mutex(monitor->mutex, update_time, monitor, NULL);
		if (monitor->call)
			monitor->call(monitor, monitor->data);
	}
	return (0);
}

int	threads(t_monitor2 *monitor, int (*callmonitor)(), int (*callthread)(), void *data)
{
	int	i;
	if (!monitor)
		return (1);
	i = -1;
	monitor->call = callmonitor;
	monitor->data = data;
	while (monitor->threads[++i])
	{
		monitor->threads[i]->call = callthread;
		monitor->threads[i]->data = data;
		pthread_create(&monitor->threads[i]->instance, NULL, call_thread, monitor->threads[i]);
		pthread_detach(monitor->threads[i]->instance);
	}
	return (call_monitor(monitor));
}

int	philosophers(t_solib *solib, int nbr_philo, char **times, int nbr_loop)
{
	t_monitor2	*monitor;

	solib->print("%d %d\n%S-------------------------\n\n",nbr_philo, nbr_loop, times);
	
	
	monitor = sothreads(solib, nbr_philo, times, nbr_loop);
	threads(monitor, monitor_update_test, thread_update_test, solib);

	//soprintf("%Cb59b28(%d)\t| (%C03dffc(MONITOR))\t\t\t: %CFF0000(philosophers has been terminated !)\n", monitor->loop->millis);
	return (0);
} 