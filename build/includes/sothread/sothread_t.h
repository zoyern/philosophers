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

typedef struct s_sothread		t_sothread;
typedef struct s_sothsync		t_sothsync;

typedef struct s_sothread {
    t_solib         *solib;
    pthread_t       instance;
    int             id;
    long            timeout;     // Temps avant la mort du philosophe
    void            *data;     // Données spécifiques à l'utilisateur (philosophe)
    int             (*callback)(struct s_sothread *, void *); // Routine du thread
	long			*millis;
	pthread_mutex_t *print;     // Mutex pour l'affichage
    pthread_mutex_t *acces;     // Mutex pour protéger l'accès aux ressources partagées
} t_sothread;

typedef struct s_sothsync {
    t_solib         *solib;
	pthread_t       instance;
    int             nbr;       // Nombre de philosophes (threads)
    int             sync;      // Nombre de fourchettes (ressources partagées)
    int             value;     // Valeur de retour de wait
	long			*millis;
	t_sothread		**threads;
    pthread_mutex_t *print;     // Mutex pour l'affichage
    pthread_mutex_t *acces;     // Mutex pour protéger l'accès aux ressources partagées
} t_sothsync;

#endif