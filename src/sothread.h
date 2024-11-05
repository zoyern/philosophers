/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_t.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almounib <almounib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 21:27:45 by marvin            #+#    #+#             */
/*   Updated: 2024/05/20 17:45:02 by almounib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOTHREAD_H
# define SOTHREAD_H

# include <sothread/sothread_t.h>


long		get_millis(void);
int			wait_sothread(t_sothsync *sync);
t_sothread	*sonew_thread(t_sothsync *sync, long timeout, int (*callback)(), void *data);
t_sothsync	*sothread(t_solib *solib, char *timeout, int (*callback)(), void *data);
t_sothsync	*sothreads(t_sothsync *sync, char *timeout, int (*callback)(), void *data);
int			sothpause(t_sothread *thread, int value, int finish);
t_sothsync	*sothsync(t_solib *solib, int nbr, int syncro);
#endif