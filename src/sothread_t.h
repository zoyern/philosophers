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
# include <limits.h>

typedef struct s_sothread		t_sothread;
typedef struct s_sothsync		t_sothsync;

typedef struct s_fork
{
	long			timeout;
	int				work;
	int				finish;
	int				death;
	int				stop;
}	t_fork;

typedef struct s_mutex
{
	int				*locked;
	int				*use;
	long			*last;
	long			*starting;
	void			*data;
	pthread_mutex_t	*instance;
}	t_mutex;

typedef struct s_sothread
{
	t_solib			*solib;
	pthread_t		instance;
	int				id;
	long			millis;
	long			nbr;
	void			*data;
	int				(*callback)();
	int				(*calldeath)();
	t_mutex			fork;
	t_mutex			acces;
	pthread_mutex_t	*start;
}	t_sothread;

typedef struct s_sothsync
{
	t_solib			*solib;
	pthread_t		instance;
	int				nbr;
	int				syncro;
	t_mutex			*forks;
	t_mutex			acces;
	pthread_mutex_t	*start;
	t_sothread		**threads;
}	t_sothsync;

#endif