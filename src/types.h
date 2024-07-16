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

typedef struct s_data
{
	int			is_alive;
	t_sotimer	*eat;
	t_sotimer	*sleep;
	t_sotimer	*think;
	t_sotimer	*dying;
}	t_data;

typedef struct s_fork
{
	int				id;
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_philosopher
{
	int		id;
	t_fork	*left_fork;
	t_fork	*right_fork;
}	t_philosopher;

typedef struct s_thread_data
{
	t_philosopher	*philosophers;
	t_fork			*forks;
	int				num_philosophers;
	pthread_t		*threads;
}	t_thread_data;

#endif