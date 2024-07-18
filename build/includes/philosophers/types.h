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

typedef struct s_philo
{
	t_solib			*solib;
	int				id;
	int				*is_dead;
	pthread_t		thread;
	pthread_mutex_t	*started;
	pthread_mutex_t	*printable;
	pthread_mutex_t	*death;
	t_sotimer		*eat;
	t_sotimer		*sleep;
	t_sotimer		*dying;
}	t_philo;

typedef struct s_monitor
{
	t_solib			*solib;
	int				*is_dead;
	int				nbr_philo;
	pthread_mutex_t	*started;
	pthread_mutex_t	*printable;
	pthread_mutex_t	*death;
	t_philo			**philos;
}	t_monitor;

#endif