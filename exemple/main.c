/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almounib <almounib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:00:14 by marvin            #+#    #+#             */
/*   Updated: 2024/05/16 14:35:26 by almounib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exemple.h"


typedef struct s_philo {
	int	loop;
	t_sotasks	**tasks;
} t_philo;


int	mutex(t_mutex mutex, int (*callback)(), void *data)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(mutex.acces);
	if (callback)
	{
		ret = callback(mutex, data);
	}
	pthread_mutex_unlock(mutex.acces);
	return (ret);
}

int	print_millis(t_mutex mutex, t_sothread *thread)
{
	(void)mutex;
	soprintf("%ld\t%d\tmillis\n", thread->millis, thread->id);
	return (0);
}


int	sothpause(t_sothread *thread, int value, int finish)
{
	pthread_mutex_lock(thread->fork.acces);
	*thread->fork.value = value;
	*thread->fork.finish = finish;
	*thread->fork.locked = 0;
	pthread_mutex_unlock(thread->fork.acces);
	return (0);
}

int	routine(t_sothread *thread, t_philo *philo)
{
	(void)thread;
	(void)philo;
	if (sotask(thread->millis, philo->tasks[thread->id], thread))
		sothpause(thread, 0, 0);
	if (philo->tasks[thread->id]->loop == philo->loop)
		return (1);
	return (0);
}


int	mutex_get_value(t_mutex mutex)
{
	int	value;

	value = *mutex.value;
	return (value);	
}

int	mutex_set_value(t_mutex mutex, int *value)
{
	return (*mutex.value = *value, *mutex.value);
}

void* sothread_routine(void* arg)
{
    t_sothread *thread = (t_sothread *)arg;  // Cast de l'argument en entier
	long		starting;
	long		death;
	int			ret;
	int			flag;

	starting = 0;
	ret = 0;
	flag = 1;
	pthread_mutex_lock(thread->thread_acces.acces);
	starting = *thread->starting;
	pthread_mutex_unlock(thread->thread_acces.acces);
	thread->millis = get_millis() - starting;
	death = thread->millis + thread->timeout;
	while (thread->millis <= death + 10)
	{
		//mutex(thread->print, print_millis, thread);
		if (mutex(thread->fork, mutex_get_value, NULL))
		{
			thread->millis = get_millis() - starting;
			if (thread->callback)
				ret = thread->callback(thread, thread->data);
			if (ret)
				break ;
			if (flag)
			{
				death = get_millis() - starting + thread->timeout;
				flag = 0;
			}
		}
		else
			flag = 1;
		thread->millis = get_millis() - starting;
	}
	if (thread->millis > death)
		ret = -1;
	if (ret < 0)
	{
		pthread_mutex_lock(thread->print.acces);
		soprintf("%ld \t%d\tdied\n", thread->millis, thread->id + 1);
		pthread_mutex_unlock(thread->print.acces);
		pthread_mutex_lock(thread->acces.acces);
		*thread->value = -1;
		pthread_mutex_unlock(thread->acces.acces);
	}
    return (NULL);
}

int	print_eat_start(long time, t_sotask *task, t_philo *philo, t_sothread *thread)
{
	(void)time;
	(void)task;
	(void)philo;
	pthread_mutex_lock(thread->print.acces);
	soprintf("%ld \t%d\tis eating\n", time, thread->id + 1);
	pthread_mutex_unlock(thread->print.acces);
	return (0);
}
int	print_sleep_start(long time, t_sotask *task, t_philo *philo, t_sothread *thread)
{
	(void)time;
	(void)task;
	(void)philo;
	pthread_mutex_lock(thread->print.acces);
	soprintf("%ld \t%d\tis sleeping\n", time, thread->id + 1);
	pthread_mutex_unlock(thread->print.acces);
	return (0);
}

int	print_eat_end(long time, t_sotask *task, t_philo *philo, t_sothread *thread)
{
	(void)time;
	(void)task;
	(void)philo;
	sothpause(thread, 1, 1);
	
	return (0);
}

int	print_think_start(long time, t_sotask *task, t_philo *philo, t_sothread *thread)
{
	(void)time;
	(void)task;
	(void)philo;
	pthread_mutex_lock(thread->print.acces);
	soprintf("%ld \t%d\tis thinking\n", time, thread->id + 1);
	pthread_mutex_unlock(thread->print.acces);
	return (0);
}

t_philo	*new_philo(t_solib *solib, int nbr_loop, char **times, int nbr)
{
	t_philo	*philo;
	int		i;

	philo = somalloc(solib, sizeof(t_philo));
	philo->tasks = somalloc(solib, sizeof(t_sotasks) * (nbr + 1));
	philo->tasks[nbr] = NULL;
	philo->loop = nbr_loop;
	i = -1;
	while (++i < nbr)
	{
		philo->tasks[i] = sotask_list(solib);
		sotask_add(philo->tasks[i], 0, sonew_task(solib, times[1], sofuncs(print_eat_start, NULL, print_eat_end), philo));
		sotask_add(philo->tasks[i], 1, sonew_task(solib, times[2], sofuncs(print_sleep_start, NULL, NULL), philo));
		sotask_add(philo->tasks[i], 2, sonew_task(solib, times[3], sofuncs(print_think_start, NULL, NULL), philo));
	}
	return (philo);
}

int		check_eat(int id, int syncro, int max, t_mutex *fork)
{
	int	i;
	int	value;
	long	time;

	i = -1;
	pthread_mutex_lock(fork[id].acces);
	value = *fork[id].eat;
	time = *fork[id].time;
	pthread_mutex_unlock(fork[id].acces);
	while (++i < syncro)
	{
		pthread_mutex_lock(fork[(id + i) % max].acces);
		if (time > *fork[(id + i) % max].time || value > *fork[i].eat)
			return (pthread_mutex_unlock(fork[(id + i) % max].acces), 1);
		pthread_mutex_unlock(fork[(id + i) % max].acces);
	}
	return (0);
}

int get_fork(int id, int syncro, int max, t_mutex *fork)
{
    if (!syncro)
        return (1);
    pthread_mutex_lock(fork[id % max].acces);
	if (!*fork[id % max].locked)
	{
		*fork[id % max].locked = 1;
		pthread_mutex_unlock(fork[id % max].acces);

		if (get_fork(id + 1, syncro - 1, max, fork))
			return (1);
		pthread_mutex_lock(fork[id % max].acces);
		*fork[id % max].locked = 0;
	}
	pthread_mutex_unlock(fork[id % max].acces);
    return (0);
}

int		test_reset(int id, int syncro, int max, t_mutex *fork)
{
	if (!syncro)
		return (1);
	pthread_mutex_lock(fork[id % max].acces);
	*fork[id % max].locked = 0;
	*fork[id % max].value = 0;
	*fork[id % max].finish = 0;
	pthread_mutex_unlock(fork[id % max].acces);
	if (test_reset(id + 1, syncro - 1, max, fork))
		return (1);
	return (0);
}

int		reset_fork(int id, int syncro, int max, t_mutex *fork)
{
	int	i;

	pthread_mutex_lock(fork[id].acces);
	if (*fork[id].finish)
	{
		*fork[id].finish = 0;
		pthread_mutex_unlock(fork[id].acces);
		i = -1;
		while (++i < syncro)
		{
			pthread_mutex_lock(fork[(id + i) % max].acces);
			*fork[(id + i) % max].locked = 0;
			pthread_mutex_unlock(fork[(id + i) % max].acces);
		}
		return (1);
	}
	pthread_mutex_unlock(fork[id].acces);
	return (0);
}

void	sync_threads(int nbr, t_sothsync *sync)
{
	int	i;
	int	j;

	i = -1;
	while (++i < nbr) // id de ma fork 
	{
		j = -1;
		while (++j < nbr) // id de ma fork 
			reset_fork(j, sync->syncro, sync->nbr, sync->forks);
		if (!check_eat(i,  sync->syncro, sync->nbr, sync->forks) && get_fork(i, sync->syncro, sync->nbr, sync->forks))
		{
			pthread_mutex_lock(sync->forks[i].acces);
			pthread_mutex_lock(sync->print.acces);
			soprintf("%ld \t%d\thas taken a fork\n", get_millis() - *sync->starting , i  + 1);
			soprintf("%ld \t%d\thas taken a fork\n", get_millis() - *sync->starting , i  + 1);
			*sync->forks[i].value = 1;
			*sync->forks[i].eat += 1;
			*sync->forks[i].time = get_millis();
			pthread_mutex_unlock(sync->forks[i].acces);
			pthread_mutex_unlock(sync->print.acces);
		}
	}
}

void* sothsync_routine(void* arg)
{
    t_sothsync *sync = (t_sothsync *)arg;  // Cast de l'argument en entier
	int		value;

	mutex(sync->acces, NULL, NULL);
	*sync->starting = get_millis();
	pthread_mutex_unlock(sync->thread_acces.acces);
	value = 0;
	while (!value)
	{
		sync_threads(sync->nbr, sync);
		pthread_mutex_lock(sync->acces.acces);
		value = *sync->value;
		pthread_mutex_unlock(sync->acces.acces);
	}
    return (NULL);
}

t_mutex	new_mutex(t_solib *solib, int locked, int value)
{
	t_mutex	fork;

	fork.acces = somalloc(solib, sizeof(pthread_mutex_t));
	fork.finish = somalloc(solib, sizeof(int));
	fork.locked = somalloc(solib, sizeof(int));
	fork.value = somalloc(solib, sizeof(int));
	fork.eat = somalloc(solib, sizeof(int));
	fork.time = somalloc(solib, sizeof(long));
	pthread_mutex_init(fork.acces, NULL);
	*fork.locked = locked;
	*fork.eat = 0;
	*fork.finish = 0;
	*fork.time = 0;
	*fork.value = value;
	return (fork);
}

t_mutex	*new_mutexs(t_solib *solib, int nbr, int locked, int value)
{
	t_mutex	*forks;
	int	i;

	i = -1;
	forks = somalloc(solib, sizeof(t_mutex) * nbr);
	while (++i < nbr)
		forks[i] = new_mutex(solib, locked, value);
	return (forks);
}

t_sothsync	*sothsync(t_solib *solib, int nbr, int syncro)
{
	t_sothsync	*sync;

	sync = somalloc(solib, sizeof(t_sothsync));
	sync->threads = somalloc(solib, sizeof(t_sothread *) * (nbr + 1));
	sync->forks = new_mutexs(solib, nbr, 0, 0);
	sync->threads[nbr] = NULL;
	sync->print = new_mutex(solib, 0, 0);
	sync->acces = new_mutex(solib, 0, 0);
	sync->thread_acces = new_mutex(solib, 0, 0);
	sync->starting = somalloc(NULL, sizeof(long));
	sync->value = somalloc(NULL, sizeof(int));
	sync->solib = solib;
	sync->nbr = nbr;
	sync->syncro = syncro;
	*sync->value = 0;
	*sync->starting = get_millis();
	pthread_mutex_lock(sync->acces.acces);
	pthread_mutex_lock(sync->thread_acces.acces);
	if (pthread_create(&sync->instance, NULL, sothsync_routine, sync))
       	return (solib->close(solib, 1), NULL);
    pthread_detach(sync->instance);
	return (sync);
}

t_sothread	*sonew_thread(t_sothsync *sync, long timeout, int (*callback)(), void *data)
{
	t_sothread	*thread;

	if (!sync)
		return (NULL);
	thread = somalloc(sync->solib, sizeof(t_sothread));
	thread->solib = sync->solib;
	thread->id = 0;
	thread->millis = 0;
	thread->value = sync->value;
	thread->timeout = timeout;
	thread->data = data;
	thread->callback = callback;
	thread->starting = sync->starting;
	thread->print = sync->print;
	thread->acces = sync->acces;
	thread->thread_acces = sync->thread_acces;
	return (thread);
}

t_sothsync	*sothread(t_solib *solib, char *timeout, int (*callback)(), void *data)
{
	t_sothsync	*sync;
	
	sync = sothsync(solib, 1, 1);
	sync->threads[0] = sonew_thread(sync, ft_atoi(timeout), callback, data);
	sync->threads[0]->fork = sync->forks[0];
	if (pthread_create(&sync->threads[0]->instance, NULL, sothread_routine, sync->threads[0]))
       	return (solib->close(solib, 1), NULL);
    pthread_detach(sync->threads[0]->instance);
	pthread_mutex_unlock(sync->acces.acces);
	return (sync);
}

t_sothsync	*sothreads(t_sothsync *sync, char *timeout, int (*callback)(), void *data)
{
	int	i;

	if (!sync)
		return (NULL);
	i = -1;
	while (++i < sync->nbr)
	{
		sync->threads[i] = sonew_thread(sync, ft_atoi(timeout), callback, data);
		sync->threads[i]->id = i;
		sync->threads[i]->fork = sync->forks[i];
		if (pthread_create(&sync->threads[i]->instance, NULL, sothread_routine, sync->threads[i]))
       		return (sync->solib->close(sync->solib, 1), NULL);
    	pthread_detach(sync->threads[i]->instance);
	}
	pthread_mutex_unlock(sync->acces.acces);
	return (sync);
}

//	soprintf("f1 :\np : %p\nmutex : %p\nlocked : %d\nvalue : %d\n\n", &fork1, fork1.acces, *fork1.locked, *fork1.value);
//	soprintf("f2 :\np : %p\nmutex : %p\nlocked : %d\nvalue : %d\n\n", &fork2, fork2.acces, *fork2.locked, *fork2.value);
int philosophers(t_solib *solib, int nbr, char **times, int nbr_loop) {

	t_philo		*philo;
	t_sothsync	*sync;
	t_sothsync	*syncs;
	(void)nbr;
	(void)times;
	(void)nbr_loop;

	// t_sothsync	*sothsync(t_solib *solib, int nbr, int syncro);
	// t_sothsync	*sothread(t_solib *solib, long timeout, int (*callback)(), void *data);
	// t_sothsync	*sothreads(t_sothsync *sync, long timeout, int (*callback)(), void *data);
	philo = new_philo(solib, nbr_loop, times, nbr);
	//sync = sothread(solib, times[0], routine, philo);
	syncs = sothreads(sothsync(solib, nbr, 2), times[0], routine, philo);
	(void)sync;
	(void)syncs;
	(void)nbr;

	int		value;

	// mutex start / acces
	pthread_mutex_lock(syncs->acces.acces);
	value = *syncs->value;
	pthread_mutex_unlock(syncs->acces.acces);
	while (!value)
	{
		pthread_mutex_lock(syncs->acces.acces);
		value = *syncs->value;
		pthread_mutex_unlock(syncs->acces.acces);
	}
	//wait_threads(threads, 1 /*blocked (permet de dire si on veux juste executer vite fais pour avoir une valeur de retour pendant l'execution du thread par exemple ou en es le programme ou si on veux bloquer le programme en attente d'une fin total des threads)*/, callback_watch /*recuperer les derniere donné et peux renvoyer un int en fonction du callback*/, philo)
	return (0);
}
//-----------------------------------------------------


int	argv_is_numeric(t_solib *solib)
{
	int	i;
	int	j;

	i = 0;
	while (solib->env->argv[i])
	{
		j = 0;
		if (solib->libft->atoi(solib->env->argv[i]) < 0)
			return (0);
		while (solib->env->argv[i][j])
		{
			if (!solib->libft->isdigit(solib->env->argv[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

char	**create_times(t_solib *solib, int get_last)
{
	char	**times;
	int		i;
	int		size;

	size = solib->env->argc - 1 - !get_last;
	times = somalloc(solib, sizeof(char *) * (size + 1));
	i = 0;
	while (i < size)
	{
		times[i] = solib->libft->strdup(solib, solib->env->argv[i + 1]);
		i++;
	}
	times[i] = NULL;
	return (times);
}

int	main(int argc, char **argv, char **envp)
{
	t_solib	*solib;

	solib = sonew_libft(sonew_types(argc, argv, envp));
	if (!solib || !solib->libft)
		return (solib->close(solib, EXIT_FAILURE));
	if ((solib->env->argc != 4 && solib->env->argc != 5)
		|| !argv_is_numeric(solib))
		return (solib->print("ERROR ARGS\n"),
			solib->close(solib, EXIT_FAILURE));
	if (!solib->env->argc)
		return (solib->close(solib, EXIT_FAILURE));
	if (solib->env->argc == 4)
		philosophers(solib, solib->libft->atoi(solib->env->argv[0]),
			create_times(solib, TRUE), -1);
	if (solib->env->argc == 5)
		philosophers(solib, solib->libft->atoi(solib->env->argv[0]),
			create_times(solib, FALSE),
			solib->libft->atoi(solib->env->argv[solib->env->argc - 1]));
	return (solib->close(solib, EXIT_SUCCESS));
}
