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

#ifndef GEARS_H
# define GEARS_H

# include <sotime/all.h>

int			sotime_loop(t_solib *solib, long millis, void *data, int (*callback)());
void		sotime_update_timer(t_solib *solib, t_sotimer *timer, int passed);
long		sotime_get_millis();
void		updating_time(t_solib *solib, int passed);
t_sotimer	sotime_timer_init(int start);

#endif
