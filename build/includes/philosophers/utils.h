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
int			mutex_get_fork(t_thread *thread);
int			check_death_all(int **lifeguard);
int			check_death_one(int **lifeguard);
int			mutex_set_fork(t_thread *thread, int **value);
int			update_stape(t_thread *thread);

// Monitor
t_monitor	*init_monitor(t_solib *solib, int nbr_philo, char **times, int nbr_loop);
int			monitor_update(t_monitor *monitor);

//Thread
t_thread	**init_thread(t_solib *solib, t_monitor *monitor);
void		*thread_update(void *arg);

//print
int	print_fork(t_thread *thread);
int	print_eating(t_thread *thread);;
int	print_thinking(t_thread *thread);
int	print_sleeping(t_thread *thread);
int	print_starting(t_monitor *monitor);

#endif
