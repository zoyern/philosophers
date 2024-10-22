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
/*
int	sothread(void);
int	sof(int f2, int func, int f1);
int	mutlock(t_mutex *mutex);
int	mutend(t_mutex *mutex);
t_mutex *new_mutex(t_solib *solib, int locked);
void* thread_routine(void* arg);
t_thread	*new_thread(t_solib *solib,  int (*condition)() , int (*routine)(), t_sync *sync);
int	wait_thread(t_thread *thread, int blocked);
long	get_millis(void);
t_sync	*thread_sync(t_solib *solib, void *data, int lock, t_sync *cpsync);
int	thread_kill(t_thread *thread);
t_thread	*new_threads(t_solib *solib,  int nbr, int syncro, t_thread *cpthread);
*/
#endif