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

#ifndef UTILS_H
# define UTILS_H

# include <philosophers/all.h>

int			mutex_get_stop(t_soloop *loop);
int			mutex_stop(t_thread *thread);
int			mutex_timer_finish(t_sotimer *timer);
int			call_mutex(pthread_mutex_t *mutex, int (*callback)(), void *data);
t_monitor	*init_monitor(t_solib *solib, int nbr_philo, char **times, int nbr_loop);
int			monitor_update(t_monitor *monitor);
t_thread	**init_thread(t_solib *solib, t_monitor *monitor);
void		*thread_update(void *arg);
t_sotimer	**create_timers(t_solib *solib, t_soloop *loop, char **strs);
int			print_init_thread(t_thread *thread);
int			print_eating(t_thread *thread);
int			print_time_eating(t_thread *thread);
#endif
