/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 21:31:29 by marvin            #+#    #+#             */
/*   Updated: 2024/06/04 16:53:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers/all.h>

int	my_update(t_solib *solib, t_data *data, long time)
{
	if (!time)
	{
		data->dying->start = 1;
		data->eat->start = solib->print("%d -- eat\n", time);
	}
	if (data->eat->finish)
		data->think->start = solib->print("%d -- think\n", time);
	if (data->think->finish)
		data->sleep->start = solib->print("%d -- sleep\n", time);
	if (data->sleep->finish)
		data->eat->start = solib->print("%d -- eat\n", time);
	if (data->dying->finish)
		solib->time->close(solib, 1);
	return (0);
}

int	philosopher(t_solib *solib, char **args)
{
	t_data	*data;

	(void)args;
	data = solib->malloc(solib, sizeof(t_data));
	data->eat = solib->time->timers->new(solib, 0, 500);
	data->think = solib->time->timers->new(solib, 0, 500);
	data->sleep = solib->time->timers->new(solib, 0, 500);
	data->dying = solib->time->timers->new(solib, 0, 5000);
	solib->time->loop(solib, 1, data, my_update);
	return (0);
}
