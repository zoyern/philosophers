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

int			sotime_loop(t_soloop *loop, long millis,
				void *data, int (*callback)());
long		sotime_get_millis(void);
void		updating_time(t_soloop *loop, int passed);
t_sotimer	sotime_timer_init(int start);
t_soloop	*soloop_init(t_solib *solib);

#endif
