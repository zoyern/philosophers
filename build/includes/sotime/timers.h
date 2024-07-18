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

t_sotimer		sotime_timer_init(int start);
t_sotimers_list	*sonew_timers_list(t_solib *solib);
t_sotimer		*timer_list_add(t_soloop *loop, int start, long millis);
void			timer_list_clear(t_soloop *loop);
void			sotime_update_timer(t_soloop *loop,
					t_sotimer *timer, int passed);

#endif
