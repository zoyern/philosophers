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

void*		sothsync_routine(void* arg);
void		sync_threads(int nbr, t_sothsync *sync);
int			check_eat(int id, int max, t_mutex *fork);
int			get_fork(int id, int syncro, int max, t_mutex *fork);
int			reset_fork(int id, int syncro, int max, t_mutex *fork);
#endif
