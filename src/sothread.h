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
int			wait_sothread(t_sothsync *sync, int (*callback)(), void *data);
t_sothread	*sonew_thread(t_sothsync *sync, int (*callback)(), int (*calldeath)(), void *data);
t_sothsync	*sothread(t_sothsync *sync, int (*callback)(), int (*calldeath)(), void *data);
t_sothsync	*sothreads(t_sothsync *sync, int (*callback)(), int (*calldeath)(), void *data);
t_sothsync	*sothsync(t_solib *solib, int nbr, int syncro, char *timeout);
void		*mutget(t_mutex mutex, void *data);
int			mutex(t_mutex mutex, int (*callback)(), void *data);
int			mutset(t_mutex mutex, int (*callback)(), void *dst, void *src);
void		free_mutex(t_solib *solib, t_mutex mutex);
void		free_mutexs(t_solib *solib, int nbr, t_mutex *mutex);
t_mutex		*new_mutexs(t_solib *solib, int nbr, void *data, int locked);
t_mutex		new_mutex(t_solib *solib, void *data, int locked);
void		th_free(t_sothread *thread);
int			th_wait(t_sothread *thread, int exit);
#endif              