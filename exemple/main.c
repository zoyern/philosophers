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
/*
typedef struct s_philo
{
    int				value;
    int				nbr_loop;
	char			**times;
}	t_philo;



int	thread_timeout(t_thread *thread, t_philo *philo)
{
	if (sof(mutend(thread->sync->time), 
		*thread->millis >= (long)sof(mutend(thread->sync->start), (long)ft_atoi(philo->times[0]), mutlock(thread->sync->start)),
		mutlock(thread->sync->time)))
		return (sof(mutend(thread->sync->die), thread_kill(thread), mutlock(thread->sync->die)), -1);
	return (0);
}

int	routine(t_thread *thread, t_philo *philo)
{
	sof(mutend(thread->sync->time),
		sof(mutend(thread->sync->print),
			soprintf("%s -  millis : %ld !\n", philo->times[0], *thread->millis),
			mutlock(thread->sync->print)),
			mutlock(thread->sync->time));
	return (0);
}

int start(t_thread *thread, t_philo *philo)
{
	sof(mutend(thread->sync->start), 0, mutlock(thread->sync->start));
	thread->condition = thread_timeout;
	return (thread->condition(thread, philo));
}

t_philo	*new_philo(t_solib *solib, char **times, int nbr_loop)
{
	t_philo	*philo;

	philo = somalloc(solib, sizeof(t_philo));

	philo->value = 0;
	philo->times = times;
	philo->nbr_loop = nbr_loop;
	return (philo);
}

int	philosophers(t_solib *solib, int nbr, char **times, int nbr_loop)
{
    t_philo		*philo;
	t_thread	*thread;
	int			ret;


	(void)nbr;
	(void)nbr_loop;
	soprintf("%s t !\n", times[0]);
	philo = new_philo(solib, times, nbr_loop);
	//thread = new_thread(solib, start, routine, thread_sync(solib, philo, 0, NULL));
	thread = new_threads(solib, nbr, 1,
			new_thread(solib, start, routine, thread_sync(solib, philo, 1, NULL)));
	(void)thread;
	while (1)
	{
		continue;
	}
	
	//ret = wait_thread(thread, 1);
	soprintf("finished return : %d -- value : %d\n", ret, philo->value);
	//status = wait_thread(thread, 1);
	new_threads(nbr, 2, routine, data);
    syncro(new_threads(solib, routine, philo, nbr), &philo->stop);
    wait_threads(solib, new_threads(solib, routine, philo), watcher, philo);
	return (0);
}



*/
typedef struct s_philo {
	int	loop;
	t_sotasks	*tasks;
} t_philo;



int	routine(t_sothread *thread, t_philo *philo)
{
	(void)thread;
	(void)philo;
	if (sotask(thread->millis, philo->tasks, thread))
		return (1); // arret du programme en mode erreur*/
	return (0);
}

void* sothread_routine(void* arg)
{
    t_sothread *thread = (t_sothread *)arg;  // Cast de l'argument en entier
	long		starting;
	long		death;

	starting = 0;
	pthread_mutex_lock(thread->acces);
	starting = *thread->starting;
	pthread_mutex_unlock(thread->acces);
	death = thread->timeout;
	thread->millis = get_millis() - starting;
	while (thread->millis <= death)
	{
		if (thread->callback)
			thread->callback(thread, thread->data);
		thread->millis = get_millis() - starting;
	}
	pthread_mutex_lock(thread->acces);
	*thread->value = 1;
	pthread_mutex_unlock(thread->acces);
    return (NULL);
}

int	print_eat_start(long time, t_sotask *task, t_philo *philo, t_sothread *thread)
{
	(void)time;
	(void)task;
	(void)philo;
	pthread_mutex_lock(thread->print);
	soprintf("%ld \t%d\ttask eat started\n", time, thread->id);
	pthread_mutex_unlock(thread->print);
	return (0);
}

int	print_eat_end(long time, t_sotask *task, t_philo *philo, t_sothread *thread)
{
	(void)time;
	(void)task;
	(void)philo;
	pthread_mutex_lock(thread->print);
	soprintf("%ld \t%d\ttask eat end\n", time, thread->id);
	pthread_mutex_unlock(thread->print);
	return (0);
}

int	print_sleep_start(long time, t_sotask *task, t_philo *philo, t_sothread *thread)
{
	(void)time;
	(void)task;
	(void)philo;
	pthread_mutex_lock(thread->print);
	soprintf("%ld \t%d\ttask sleep started\n", time, thread->id);
	pthread_mutex_unlock(thread->print);
	return (0);
}

int	print_sleep_end(long time, t_sotask *task, t_philo *philo, t_sothread *thread)
{
	(void)time;
	(void)task;
	(void)philo;
	pthread_mutex_lock(thread->print);
	soprintf("%ld \t%d\ttask sleep end\n", time, thread->id);
	pthread_mutex_unlock(thread->print);
	return (0);
}

int	print_think_start(long time, t_sotask *task, t_philo *philo, t_sothread *thread)
{
	(void)time;
	(void)task;
	(void)philo;
	pthread_mutex_lock(thread->print);
	soprintf("%ld \t%d\ttask think started\n", time, thread->id);
	pthread_mutex_unlock(thread->print);
	return (0);
}

int	print_think_end(long time, t_sotask *task, t_philo *philo, t_sothread *thread)
{
	(void)time;
	(void)task;
	(void)philo;
	pthread_mutex_lock(thread->print);
	soprintf("%ld \t%d\ttask think end\n", time, thread->id);
	pthread_mutex_unlock(thread->print);
	return (0);
}


t_philo	*new_philo(t_solib *solib, int nbr_loop, char **times)
{
	t_philo	*philo;

	philo = somalloc(solib, sizeof(t_philo));
	philo->loop = nbr_loop;
	philo->tasks = sotask_list(solib);
	sotask_add(philo->tasks, 0, sonew_task(solib, times[1], sofuncs(print_eat_start, NULL, print_eat_end), philo));
	sotask_add(philo->tasks, 1, sonew_task(solib, times[2], sofuncs(print_sleep_start, NULL, print_sleep_end), philo));
	sotask_add(philo->tasks, 2, sonew_task(solib, times[3], sofuncs(print_think_start, NULL, print_think_end), philo));
	return (philo);
}


void* sothsync_routine(void* arg)
{
    t_sothsync *sync = (t_sothsync *)arg;  // Cast de l'argument en entier
	int		value;

	// mutex start / acces
	pthread_mutex_lock(sync->acces);
	*sync->starting = get_millis();
	value = *sync->value;
	pthread_mutex_unlock(sync->acces);
	while (!value)
	{
		pthread_mutex_lock(sync->acces);
		value = *sync->value;
		pthread_mutex_unlock(sync->acces);
	}
    return (NULL);
}


t_sothsync	*sothsync(t_solib *solib, int nbr, int syncro)
{
	t_sothsync	*sync;

	sync = somalloc(solib, sizeof(t_sothsync));
	sync->threads = somalloc(solib, sizeof(t_sothread *) * (nbr + 1));
	sync->threads[nbr] = NULL;
	sync->print = somalloc(solib, sizeof(pthread_mutex_t));
	sync->acces = somalloc(solib, sizeof(pthread_mutex_t));
	sync->starting = somalloc(NULL, sizeof(long));
	sync->value = somalloc(NULL, sizeof(int));
	sync->solib = solib;
	sync->nbr = nbr;
	sync->sync = syncro;
	*sync->value = 0;
	*sync->starting = get_millis();
	pthread_mutex_init(sync->print, NULL);
	pthread_mutex_init(sync->acces, NULL);
	pthread_mutex_lock(sync->acces);
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
	return (thread);
}

t_sothsync	*sothread(t_solib *solib, char *timeout, int (*callback)(), void *data)
{
	t_sothsync	*sync;
	
	sync = sothsync(solib, 1, 1);
	sync->threads[0] = sonew_thread(sync, ft_atoi(timeout), callback, data);
	if (pthread_create(&sync->threads[0]->instance, NULL, sothread_routine, sync->threads[0]))
       	return (solib->close(solib, 1), NULL);
    pthread_detach(sync->threads[0]->instance);
	pthread_mutex_unlock(sync->acces);
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
		if (pthread_create(&sync->threads[i]->instance, NULL, sothread_routine, sync->threads[i]))
       		return (sync->solib->close(sync->solib, 1), NULL);
    	pthread_detach(sync->threads[i]->instance);
	}
	pthread_mutex_unlock(sync->acces);
	return (sync);
}

int philosophers(t_solib *solib, int nbr, char **times, int nbr_loop) {

	t_philo		*philo;
	t_sothsync	*sync;
	t_sothsync	*syncs;
	

	// t_sothsync	*sothsync(t_solib *solib, int nbr, int syncro);
	// t_sothsync	*sothread(t_solib *solib, long timeout, int (*callback)(), void *data);
	// t_sothsync	*sothreads(t_sothsync *sync, long timeout, int (*callback)(), void *data);
	philo = new_philo(solib, nbr_loop, times);
	//sync = sothread(solib, times[0], routine, philo);
	syncs = sothreads(sothsync(solib, nbr, 2), times[0], routine, philo);
	(void)sync;
	(void)syncs;
	(void)nbr;

	int		value;

	// mutex start / acces
	pthread_mutex_lock(syncs->acces);
	value = *syncs->value;
	pthread_mutex_unlock(syncs->acces);
	while (!value)
	{
		pthread_mutex_lock(syncs->acces);
		value = *syncs->value;
		pthread_mutex_unlock(syncs->acces);
	}
	
	soprintf("finished task nbr: %d loop : %d\n", philo->tasks->count, philo->tasks->loop);
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
