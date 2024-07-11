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

int	philosopher(t_solib *solib)
{
	(void)solib;
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

void	redisplay(t_solib *solib)
{
		solib->print("%Cclear()");
		solib->print("%BFFFFFF( %CFF0000(COUCOU)                                                                                                              \n)");
		solib->print("%BFFFFFF(                                                                                                                       \n)");
		solib->print("%B543709(                                                                                                                       \n)");
		solib->print("%B543709(                                                                                                                       \n)");
		solib->print("%B543709(                                                                                                                       \n)");
		solib->print("%BFFFFFF(                                                                                                                       \n)");
		solib->print("%BFFFFFF(                                                                                                                       \n)");
		solib->print("%BFFFFFF(                                                                                                                       \n)");
		solib->print("%BFFFFFF(                                                                                                                       \n)");
		sleep(2);
}

int	core(t_solib *solib)
{
	t_data	*data;

	data = solib->malloc(solib, sizeof(t_data));
	data->time = sonew_time(solib);
	while (1)
	{
		redisplay(solib);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_solib	*solib;

	solib = sonew_libft(sonew_types(argc, argv, envp));
	if (!solib)
		return (solib->close(solib, EXIT_FAILURE));
	if ((solib->env->argc != 3 && solib->env->argc != 4) || !argv_is_numeric(solib))
		return (solib->print("ERROR ARGS\n"));
	core(solib);
	return (solib->close(solib, EXIT_SUCCESS));
}
