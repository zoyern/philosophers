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


void	sotime_init(t_sotime *sotime)
{
	sotime->starting_time = 0;
	sotime->millis = 0;
	sotime->loop = 0;
	sotime->current = sotime->starting_time;
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
	return (solib);
}
