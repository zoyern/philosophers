/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almounib <almounib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:59:30 by marvin            #+#    #+#             */
/*   Updated: 2024/05/16 14:39:01 by almounib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOTHREAD_T_H
# define SOTHREAD_T_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <sotypes.h>
# include <solibft.h>

typedef struct s_thread	t_thread;
typedef struct s_mutex	t_mutex;
/*
typedef struct s_mutex
{
    int				lock;
    pthread_mutex_t	*instance;
}	t_mutex;

typedef struct s_sync
{
	int				id;
    pthread_t       instance;
	t_mutex			*print;
	t_mutex			*start;
	t_mutex			*time;
	t_mutex			*die;
	int				*fork; // tab de 2 int ou plus selon syncro // mutex start
	int				*work; // mutex start
	int				**alive; // mutex die
	int				*value; // mutex die
	long			*starting;
	long			*millis;
	long			*loop;
	int				*nbr;
	int				*syncro;
	void			*data;
	
}	t_sync;

typedef struct s_thread
{
	t_sync			*sync;
    int				id;
	long			*millis; // mutex time
	int				*alive; // mutex die
	int				*value; // mutex die
	long			*loop; // mutex start
	void            *data;
	int             (*routine)();
	int             (*condition)();
}	t_thread;

*/

typedef struct s_pswp		t_pswp;
typedef struct s_philo		t_philo;

typedef struct s_thread {
    pthread_t thread;
    t_solib *solib;
    int sync;
    t_philo *philo;
	long time;
    pthread_mutex_t *print;
    pthread_mutex_t *forks;
    int start;
} t_thread;

#endif