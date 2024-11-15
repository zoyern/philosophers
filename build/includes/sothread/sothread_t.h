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
#include <limits.h>

typedef struct s_sothread		t_sothread;
typedef struct s_sothsync		t_sothsync;

typedef struct s_fork {
	long			timeout;
	int				work; // acces partager
	int				finish; // acces partager
	int				death; 
	int				stop; // acces partager
} t_fork;

typedef struct s_mutex {
	int				*locked; // si le mutex est lisib
	int				*use; // si le mutex est lisib // + 1 a chaque mutset
	long			*last; // si le mutex est lisib // se set a chaque mutset
	long			*starting; // si le mutex est lisib // se set a chaque mutset
	void			*data; // s'envoie directement dans le callback
	pthread_mutex_t *instance; // le mutex en lui meme
} t_mutex;

typedef struct s_sothread {
	t_solib         *solib;
	pthread_t       instance;
	int             id;
	long			millis;
	long			nbr;
	void            *data;     // Données spécifiques à l'utilisateur (philosophe)
	int             (*callback)(); // Routine du thread
	int             (*calldeath)(); // Routine du thread
	t_mutex			fork;
	t_mutex			acces;     // Mutex pour protéger l'accès aux ressources partagées
	pthread_mutex_t	*start;
} t_sothread;

typedef struct s_sothsync {
	t_solib         *solib;
	pthread_t       instance;
	int             nbr;       // Nombre de philosophes (threads)
	int             syncro;      // Nombre de fourchettes (ressources partagées) 4 
	t_mutex			*forks;
	t_mutex			acces;     // Mutex pour protéger l'accès aux ressources partagées
	pthread_mutex_t	*start;     // Mutex pour protéger l'accès aux ressources partagées
	t_sothread		**threads;
} t_sothsync;

#endif