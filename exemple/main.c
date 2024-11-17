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
		sotask_add(philo->tasks[i], 0, sonew_task(solib, times[1],
				sofuncs(NULL, NULL, print_eat_end), philo));
		sotask_add(philo->tasks[i], 1, sonew_task(solib, times[2],
				sofuncs(print_sleep_start, NULL, NULL), philo));
		sotask_add(philo->tasks[i], 2, sonew_task(solib, times[3],
				sofuncs(print_think_start, NULL, NULL), philo));
	}
	return (philo);
}

int	philosophers(t_solib *solib, int nbr, char **times, int nbr_loop)
{
	t_philo		*philo;
	t_sothsync	*syncs;

	philo = new_philo(solib, nbr_loop, times, nbr);
	syncs = sothreads(sothsync(solib, nbr, 2, times[0]),
			routine, print_died, philo);
	wait_sothread(syncs, NULL, NULL);
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
		if (ft_strlen(solib->env->argv[i]) > 10)
			return (0);
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
