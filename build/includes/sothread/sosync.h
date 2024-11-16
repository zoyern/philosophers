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

#ifndef SOSYNC_H
# define SOSYNC_H

# include <sothread/all.h>

void		*sothsync_routine(void *arg);
int			thsync_glouton(t_sothsync *sync, int id, t_mutex *mutex);
void		thsync_finish(t_sothsync *sync, int id, t_mutex *mutex);
void		thsync_work(t_sothsync *sync, int id, t_mutex *mutex, long time);
void		thsync_calldeath(t_sothsync *sync, int id, long time);
int			thsync_death(t_sothsync *sync, t_mutex *mutex, long time);
int			protect_modulo(int nbr, int mod);
void		thsync_lock(t_sothsync *sync, int id, t_mutex *mutex, long time);
void		thsync_unlock(t_sothsync *sync, int id, t_mutex *mutex);

#endif
