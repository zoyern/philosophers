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
#include <sys/time.h>

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

void	redisplay(t_solib *solib)
{
		solib->print("%Cclear()");
		usleep(500);
}

long	change_to_positive(long new, long old)
{
	int	new_nbr;

	if (new < old)
		printf("--- 1 ------ ");
	new_nbr = new;
	if (new < 0)
		new_nbr = new * -1;
	return (new_nbr);
}

long	getCurrentTimeInMillis()
{
    struct timeval	time;

    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000) + (time.tv_usec / 1000);
}

void	updating_time(t_sotime *sotime)
{
	sotime->current = getCurrentTimeInMillis();
	sotime->millis = sotime->current - sotime->starting_time;
}

int	callback_test()
{
	return (0);
}

int	start_timer(t_solib *solib, t_sotimer *timer, long millis)
{
	if (timer->start && !timer->working)
	{
		//commencer le comptage
		timer->start_millis = solib->time->millis;
		timer->millis = 0;
		timer->finish = 0;
		timer->working = 1;
	}
	//printf("%ld\n", timer->millis);
	if (timer->working && !timer->finish && timer->millis >= millis)
	{
		timer->finish = 1;
		timer->start = 0;
		timer->working = 0;
		return (1);
	}
	timer->millis = solib->time->millis - timer->start_millis;
	return (0);
}

//eat sleep think

int	my_update(t_solib *solib, t_data *data, long time)
{
	//redisplay(solib);
	(void)time;
	int	t1;
	int	t2;

	t1 = 0;
	t2 = 0;
	if (data->test.start)
		t1 = start_timer(solib, &data->test, 2000);
	if (data->test2.start)
		t2 = start_timer(solib, &data->test2, 4000);
	if (t1)
	{
		printf("coucou : \n");
		data->test.start = 1;
		data->test2.start = 1;
	}
	if (t2)
	{
		printf("\tje suis alexis \n");
		data->test.start = 1;
	}
	/*if (data->test2.start)
	{
		printf("\tje suis alexis \n");
		data->test.start = start_timer(solib, &data->test2, 2000);
	}*/
	return (0);
}

int	sotime_loop(t_solib *solib, long millis, void *data, int (*callback)())
{
	if (!solib || !solib->time)
		return (1);
	solib->time->loop = 1;
	solib->time->starting_time = getCurrentTimeInMillis();
	long	start = solib->time->millis - millis;
	long	start_ti = solib->time->millis;
	while (solib->time->loop)
	{
		if (solib->time->millis - start >= millis)
		{
			//if (solib->time->millis - start >= millis)
			if (callback)
				if (callback(solib, data, solib->time->millis - start_ti))
					return (1);
			start = solib->time->millis;
		}
		updating_time(solib->time);
	}
	return (0);
}

int	core(t_solib *solib)
{
	t_data	*data;

	data = solib->malloc(solib, sizeof(t_data));
	data->test.start = 1;
	sotime_loop(solib, 500, data, my_update);
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
