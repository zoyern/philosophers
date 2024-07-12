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

int	philosopher(t_solib *solib, char **args)
{
	(void)solib;
	(void)args;
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

int	my_update(t_solib *solib, t_data *data, long time)
{
	if (!time)
		data->eat->start = solib->print("%d -- eat\n", time);
	if (data->eat->finish)
		data->think->start = solib->print("%d -- think\n", time);
	if (data->think->finish)
		data->sleep->start = solib->print("%d -- sleep\n", time);
	if (data->sleep->finish)
		data->eat->start = solib->print("%d -- eat\n", time);
	return (0);
}

int	core(t_solib *solib)
{
	t_data	*data;

	data = solib->malloc(solib, sizeof(t_data));
	data->eat = solib->time->timers->add(solib, 0, 2000);
	data->think = solib->time->timers->add(solib, 0, 2000);
	data->sleep = solib->time->timers->add(solib, 0, 2000);
	data->dying = solib->time->timers->add(solib, 0, 2000);
	solib->time->loop(solib, 1, data, my_update);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_solib	*solib;

	solib = sonew_libft(sonew_types(argc, argv, envp));
	if (!solib)
		return (solib->close(solib, EXIT_FAILURE));
	if ((solib->env->argc != 3 && solib->env->argc != 4)
			|| !argv_is_numeric(solib))
		return (solib->print("ERROR ARGS\n"));
	solib = sonew_time(solib);
	if (!solib->time)
		return (solib->close(solib, EXIT_FAILURE));
	core(solib);
	return (solib->close(solib, EXIT_SUCCESS));
}
