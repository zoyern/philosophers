/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 20:22:15 by marvin            #+#    #+#             */
/*   Updated: 2024/04/07 20:22:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIMERS_H
# define TIMERS_H

# include <sotime/all.h>

int			sotime_start_timer(t_solib *solib, t_sotimer *timer, long millis);
t_sotimer	sotime_timer_init(int start);
void		sonew_timers_list(t_solib *solib);
t_sotimer	*timer_list_add(t_solib *solib, int start, long millis);	

#endif
