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

#include <sotime/all.h>

int	sotime_close(t_solib *solib, int status)
{
	solib->time->stop = 1;
	if (!solib)
	{
		free(solib->time);
		if (status)
			exit(status);
		return (status);
	}
	if (status)
		solib->close(solib, status);
	return (status);
}

void	sotime_init(t_sotime *sotime)
{
	sotime->starting_time = 0;
	sotime->millis = 0;
	sotime->stop = 1;
	sotime->current = sotime->starting_time;
	sotime->loop = sotime_loop;
	sotime->get_millis = sotime_get_millis;
	sotime->update = updating_time;
	sotime->close = sotime_close;
}

t_solib	*sonew_time(t_solib *solib)
{
	t_sotime	*sotime;

	if (!solib)
		return (NULL);
	if (!solib->libft)
		solib = sonew_libft(solib);
	if (!solib->libft)
		solib->close(solib, EXIT_FAILURE);
	sotime = (t_sotime *)solib->malloc(solib, sizeof(t_sotime));
	if (!sotime)
		solib->close(solib, EXIT_FAILURE);
	sotime_init(sotime);
	solib->time = sotime;
	sonew_timers_list(solib);
	return (solib);
}
