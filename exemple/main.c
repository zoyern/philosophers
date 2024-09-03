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
	int				id;
	int				*stop;
	int				*alive;
	long			*millis;
	long			*starting;
	char			**times;
	long			*tasks;
	pthread_mutex_t	**forks;
	pthread_mutex_t	*mutex;
}	t_philo;

long	get_millis(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}



int		mutex2(t_philo *thread, pthread_mutex_t *mutex, int (*callback)(), long *millis)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(mutex);
	*millis = get_millis() - *thread->starting;
	if (callback)
		ret = callback(thread);
	pthread_mutex_unlock(mutex);
	return (ret);
}

int	print_takefork(t_philo *thread)
{
	//thread->lastoc = get_millis();
	soprintf("%Cb59b28(%lld)\t| (%C03dffc(%d)) : %Cd62d54(has taken a fork)\n", *thread->millis, thread->id);
	soprintf("%Cb59b28(%lld)\t| (%C03dffc(%d)) : %Cd62d54(has taken a fork)\n", *thread->millis, thread->id);
	soprintf("%Cb59b28(%lld)\t| (%C03dffc(%d)) : %Cd62d54(is eating)\n", *thread->millis, thread->id);
	thread->tasks[1] = *thread->millis + (ft_atoi(thread->times[1]));
	thread->tasks[0] = *thread->millis + (ft_atoi(thread->times[0]));
	return (0);
}

int	print_sleeping2(t_philo *thread)
{
	soprintf("%Cb59b28(%lld)\t| (%C03dffc(%d)) : %Cd62d54(is sleeping)\n", *thread->millis, thread->id);
	thread->tasks[2] = *thread->millis + (ft_atoi(thread->times[2]));
	return (0);
}

int	print_thinking2(t_philo *thread)
{
	soprintf("%Cb59b28(%lld)\t| (%C03dffc(%d)) : %Cd62d54(is thinking)\n", *thread->millis, thread->id);
	return (0);
}

int	wait_task(t_philo *thread, int id)
{
	while (1)
	{
		pthread_mutex_lock(thread->mutex);
		// return si death
		if (*thread->millis >= thread->tasks[id])
			return (pthread_mutex_unlock(thread->mutex), 0);
		pthread_mutex_unlock(thread->mutex);
	}
	return (0);
}

int	takefork_other(t_philo *thread)
{
	// je bloque une fouchette
	pthread_mutex_lock(thread->forks[0]);
	 // je bloque une deuxieme fourchette
	pthread_mutex_lock(thread->forks[1]);
	// je verifie si je ne suis pas mort 
	// je print que j'ai pris 2 fourchette donc je mange donc je start le chrono de eat
	mutex2(thread, thread->mutex, print_takefork, thread->millis);
	if (wait_task(thread, 1)) // verifie si mort 1
		return (1); // redonne les fourchette et close car mort
	mutex2(thread, thread->mutex, print_sleeping2, thread->millis); // print sleep et start sleep
	if (wait_task(thread, 2))
		return (1); // redonne les fourchette et close car mort
	pthread_mutex_unlock(thread->forks[0]); // unlock les fourchette
	pthread_mutex_unlock(thread->forks[1]);	// unlock les fourchette
	// attend pour print permet de laisser le temps pour qu'il ne reprennent pas de suite une fourchette
	mutex2(thread, thread->mutex, print_thinking2, thread->millis); 
	return (0);
}

void* thread_function(void* arg)
{
    t_philo *thread = (t_philo *)arg;  // Cast de l'argument en entier

	while (1)
		takefork_other(thread);
    return NULL;
}

long	*create_tasks(char **times)
{
	long	*tasks;
	long	len;
	long	i;

	len = 0;
	while (times[len])
		len++;
	tasks = malloc(sizeof(long) * (len));
	i = 0;
	tasks[i] = ft_atoi(times[i]);
	while (++i < len)
			tasks[i] = 0;
	return (tasks);
}

int	philosophers(t_solib *solib, int nbr_philo, char **times, int nbr_loop)
{
	solib->print("%d %d\n%S-------------------------\n\n",nbr_philo, nbr_loop, times);
	
	pthread_t threads[nbr_philo];  // Tableau pour stocker les identifiants des threads
    long	*starting = malloc(sizeof(long));
	long	*millis = malloc(sizeof(long));
	int		*stop = malloc(sizeof(int));
	*stop = 0;
    int i = -1;
	*millis = 0;
    pthread_mutex_t	**forks = malloc(sizeof(pthread_mutex_t *) * (nbr_philo + 1));
	forks[nbr_philo] = NULL;
    int				**peacemaker = malloc(sizeof(int *) * (nbr_philo + 1));
	peacemaker[nbr_philo] = NULL;
	while (++i < nbr_philo)
	{
		forks[i] = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(forks[i], NULL);
	}
    // Créer N threads
	pthread_mutex_t *mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(mutex, NULL);
	pthread_mutex_lock(mutex);
	i = 0;
    while (i < nbr_philo)
    {
		t_philo *thread = malloc(sizeof(t_philo));
		thread->id = i;
		thread->stop = stop;
		thread->mutex = mutex;
		thread->millis = millis;
		thread->times = times;
		thread->starting = starting;
		thread->forks = malloc(sizeof(pthread_mutex_t *) * 2);
		thread->alive = malloc(sizeof(int));
		*thread->alive = 1;
		peacemaker[i] = thread->alive;
		thread->forks[0] = forks[i];
		thread->forks[1] = forks[(i + 1) % nbr_philo];
		thread->tasks = create_tasks(times);
        if (pthread_create(&threads[i], NULL, thread_function, thread))
        {
            fprintf(stderr, "Erreur de création de thread %d\n", i);
            return 1;
        }
		else
			pthread_detach(threads[i]);
        i++;
    }
	*starting = get_millis();
    pthread_mutex_unlock(mutex);
	while (1)
	{
		pthread_mutex_lock(mutex);
		*millis = get_millis() - *starting;
		pthread_mutex_unlock(mutex);
	}
	
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
	soprintf("%Cb59b28(%lld)\t| (%C03dffc(MONITOR))\t\t\t: %CFF0000(philosophers has been terminated !)\n", 0);
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
