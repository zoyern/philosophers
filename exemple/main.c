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
#include <stdio.h>
#include <solibft/sostdlib.h>
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
    int id;
    int has_eaten;
	int	loop;
    int forks_taken;
    long time;
	t_sotasks	*tasks;
} t_philo;

//----------------------------------------------
/*
{pthread_mutex_lock(mutex->instance), mutex->lock = 1)
	return (mutex->lock = 0, pthread_mutex_unlock(mutex->instance));
int	mutex(t_mutex *mutex, int (*callback)(), void *data)
{
	mutex_lock(mutex);
	if (callback)
		callback(data);
	mutex_unlock(mutex);
}



int	sotask(long time, t_task *task, void *data)
{	
	// verifie la premiere  task avec time execute le callback donné avec la data et si la task est fini le notifier avec task_print et si ca a fait un tour complet le notifier aussi d'une maniere ou une autre
}

int	routine(t_tread *thread, t_philo *philo) // this is while 1 but blocked if cant eat (fork not accesible)
{
	if (sotask(time, philo->task, thread))
		return (1) // arret du programme en mode erreur 
}

*/

int	task_print(long time, t_sotask *task)
{
	if (task->id == 0 && task->start)
		soprintf("%ld task eat started\n", time);
	if (task->id == 0 && task->end)
		soprintf("%ld task eat end\n", time);
	if (task->id == 1 && task->start)
		soprintf("%ld task sleep started\n", time);
	if (task->id == 1 && task->end)
		soprintf("%ld task sleep end\n", time);
	if (task->id == 2 && task->start)
		soprintf("%ld task think started\n", time);
	if (task->id == 2 && task->end)
		soprintf("%ld task think end\n", time);
	return (0);
}

t_philo	*new_philo(t_solib *solib, int nbr_loop)
{
	t_philo	*philo;

	philo = somalloc(solib, sizeof(t_philo));
	philo->loop = nbr_loop;
	philo->tasks = sotask_list(solib);
	return (philo);
}

int	get_time(long current, long *starting, long last)
{
	long	millis;

	millis = current - *starting;
	if (millis - last > 1)
		return (*starting += millis - last,
			(millis -= (millis - last) + 1), millis);
	return (millis);
}

int philosophers(t_solib *solib, int nbr, char **times, int nbr_loop) {

	t_philo	*philo;
	long	starting;
	long	millis;
	
	(void)nbr;
	philo = new_philo(solib, nbr_loop);
	sotask_add(philo->tasks, 0, sonew_task(solib, times[1], task_print, philo));
	sotask_add(philo->tasks, 1, sonew_task(solib, times[2], task_print, philo));
	sotask_add(philo->tasks, 2, sonew_task(solib, times[3], task_print, philo));
	
	millis = 0;
	starting = get_millis();
	while (philo->tasks->loop < 5)
	{
		millis = get_time(get_millis(), &starting, millis);
		if (sotask(millis, philo->tasks, NULL))
			soprintf("%C#FF0000(tasks finished)\n");
	}
	soprintf("finished task nbr: %d loop : %d\n", philo->tasks->count, philo->tasks->loop);
	/*t_threads *threads = sothreads(solib, nbr, 2, routine);
	mutex(threads->print, print_helloworld, NULL);*/
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
	times = solib->malloc(solib, sizeof(char *) * (size + 1));
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
	if (!solib)
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
