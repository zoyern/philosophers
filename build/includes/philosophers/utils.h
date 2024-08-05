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

//Mutex
int			call_mutex(pthread_mutex_t *mutex, int (*callback)(), void *data, void *data2);
int			mutex_get_int(int *value);
int			call_death(t_thread *thread, t_monitor *monitor);
int			death_monitor(t_monitor *monitor);
int			death_thread(t_thread *thread);
int			simul_take_fork(t_thread *thread);
int			check_death_all(int **lifeguard);
int			check_death_one(int **lifeguard);

// Monitor
t_monitor	*init_monitor(t_solib *solib, int nbr_philo, char **times, int nbr_loop);
int			monitor_update(t_monitor *monitor);

//Thread
t_thread	**init_thread(t_solib *solib, t_monitor *monitor);
void		*thread_update(void *arg);

#endif
