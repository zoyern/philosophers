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


typedef struct s_philo
{
	int				id;
	pthread_mutex_t	**forks;
	pthread_mutex_t	*mutex;
}	t_philo;

int		mutex2(pthread_mutex_t *mutex, int (*callback)(), void *var, void *value)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(mutex);
	if (callback)
		ret = callback(var, value);
	pthread_mutex_unlock(mutex);
	return (ret);
}

int	print_takefork(t_philo *thread)
{
	soprintf("%Cb59b28(%d)\t| (%C03dffc(%d)) : %Cd62d54(has taken a fork)\n", 0, thread->id);
	return (0);
}

int	print_eating2(t_philo *thread)
{
	soprintf("%Cb59b28(%d)\t| (%C03dffc(%d)) : %Cd62d54(is eating)\n", 0, thread->id);
	return (0);
}

int	print_sleeping2(t_philo *thread)
{
	soprintf("%Cb59b28(%d)\t| (%C03dffc(%d)) : %Cd62d54(is sleeping)\n", 0, thread->id);
	return (0);
}

int	print_thinking2(t_philo *thread)
{
	soprintf("%Cb59b28(%d)\t| (%C03dffc(%d)) : %Cd62d54(is thinking)\n", 0, thread->id);
	return (0);
}

int	redem_fork(t_philo *thread)
{
	pthread_mutex_unlock(thread->forks[0]);
	pthread_mutex_unlock(thread->forks[1]);
	return (0);
}

int	takefork_mine(t_philo *thread)
{
	pthread_mutex_lock(thread->forks[0]);
	mutex2(thread->mutex, print_takefork, thread, NULL);
	return (0);
}

int	takefork_other(t_philo *thread)
{
	pthread_mutex_lock(thread->forks[1]);
	takefork_mine(thread);
	mutex2(thread->mutex, print_takefork, thread, NULL);
	return (0);
}

void* thread_function(void* arg)
{
    t_philo *thread = (t_philo *)arg;  // Cast de l'argument en entier
	if (thread->id)
		mutex2(thread->mutex, NULL, NULL, NULL);
	while (1)
	{
		takefork_other(thread);//takefork(thread->id, thread->forks[0]);
		mutex2(thread->mutex, print_eating2, thread, NULL);
		usleep(2000 * 1000);
		mutex2(thread->mutex, print_sleeping2, thread, NULL);
		usleep(2000 * 1000);
		mutex2(thread->mutex, print_thinking2, thread, NULL);
		pthread_mutex_unlock(thread->forks[0]);
		pthread_mutex_unlock(thread->forks[1]);
	}
    // Simule du travail en mettant en pause le thread pendant 1 seconde
    return NULL;
}

int	philosophers(t_solib *solib, int nbr_philo, char **times, int nbr_loop)
{
	solib->print("%d %d\n%S-------------------------\n\n",nbr_philo, nbr_loop, times);
	
	pthread_t threads[nbr_philo];  // Tableau pour stocker les identifiants des threads
    
    int i = 0;
    pthread_mutex_t	**forks = malloc(sizeof(pthread_mutex_t *) * (nbr_philo + 1));
	while (i < nbr_philo)
	{
		forks[i] = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(forks[i], NULL);
		i++;
	}
	i = 0;
    // Créer N threads
	pthread_mutex_t *mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(mutex, NULL);
	pthread_mutex_lock(mutex);
	printf("hey`\n");
    while (i < nbr_philo)
    {
		t_philo *thread = malloc(sizeof(t_philo));
		thread->id = i;
		thread->mutex = mutex;
		thread->forks = malloc(sizeof(pthread_mutex_t *) * 2);
		thread->forks[0] = forks[i];
		thread->forks[1] = forks[(i + 1) % nbr_philo];
        if (pthread_create(&threads[i], NULL, thread_function, thread))
        {
            fprintf(stderr, "Erreur de création de thread %d\n", i);
            return 1;
        }
        i++;
    }
    pthread_mutex_unlock(mutex);
    i = 0;
    
    // Attendre la fin des N threads
    while (i < nbr_philo)
    {
        if (pthread_join(threads[i], NULL))
        {
            fprintf(stderr, "Erreur lors du join du thread %d\n", i);
            return 2;
        }
        i++;
    }
	soprintf("%Cb59b28(%d)\t| (%C03dffc(MONITOR))\t\t\t: %CFF0000(philosophers has been terminated !)\n", 0);
	return (0);
}









































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
	solib = sonew_time(solib);
	if (!solib->time || !solib->env->argc)
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
