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

typedef struct s_philo
{
    int				value;
    int				nbr_loop;
	char			**times;
}	t_philo;



int	thread_timeout(t_thread *thread, t_philo *philo)
{
	sof(mutend(thread->sync->print), soprintf("%p -- %p -- %p\n", thread->sync->time, thread->sync->start, philo->times), mutlock(thread->sync->print));
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
	thread = new_thread(solib, start, routine, thread_sync(solib, philo, 0, NULL));
	/*thread = new_threads(solib, nbr, 1,
			new_thread(solib, start, routine, thread_sync(solib, philo, 1, NULL)));*/
	
	ret = wait_thread(thread, 1);
	soprintf("finished return : %d -- value : %d\n", ret, philo->value);
	//status = wait_thread(thread, 1);
	/*new_threads(nbr, 2, routine, data);
    syncro(new_threads(solib, routine, philo, nbr), &philo->stop);
    wait_threads(solib, new_threads(solib, routine, philo), watcher, philo);*/
	return (0);
}








// temps to die = timeout fork = syncro evité d'épuisé la memoire trop vite double ( comprendre le system de rendement pour des double et voir si on peux faire des triple ou autre)

















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
