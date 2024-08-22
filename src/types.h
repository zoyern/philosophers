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

#ifndef TYPES_H
# define TYPES_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sotypes.h>
# include <solibft.h>
# include <sotime.h>

typedef struct s_thread			t_thread;
typedef struct s_monitor		t_monitor;
typedef struct s_threadb		t_threadb;
typedef struct s_monitorb		t_monitorb;

typedef struct s_thread
{
	int				id;
	int				need_fork;
	int				*stop;
	int				*stape;
	int				**life_guard;
	int				**acces;
	int				nbr_loop;
	int				nbr_philo;
	t_monitor		*monitor;
	t_soloop		*loop;
	t_sotimer		**times;
	pthread_t		instance;
	pthread_mutex_t	*printable;
	pthread_mutex_t	*stoped;
	pthread_mutex_t	*take;
}	t_thread;

typedef struct s_monitor
{
	t_soloop		*loop;
	t_thread		**threads;
	int				*stop;
	int				*stape;
	int				**life_guard;
	int				**acces;
	int				nbr_loop;
	int				current_loop;
	int				nbr_philo;
	char			**times;
	pthread_mutex_t	*printable;
	pthread_mutex_t	*stoped;
	pthread_mutex_t	*take;
}	t_monitor;

typedef struct s_threadb
{
	int				id;
	int				stop;
	int				*fork;
	int				**task;
	int				count;
	void			*data;
	int 			(*call)();
	pthread_t		instance;
	pthread_mutex_t	*mutex;
	t_monitorb		*monitor;
}	t_threadb;

typedef struct s_monitorb
{
	int				stop;
	t_threadb		**threads;
	int				**forks;
	long			***tasks;
	long			millis;
	long			starting;
	long			last_time;
	long			nbr;
	long			loop;
	void			*data;
	int				(*call)();
	pthread_mutex_t	*mutex;
	t_solib			*solib;
}	t_monitorb;

#endif