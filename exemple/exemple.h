/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exemple.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almounib <almounib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 21:27:45 by marvin            #+#    #+#             */
/*   Updated: 2024/05/16 14:43:35 by almounib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEMPLE_H
# define EXEMPLE_H

# include <unistd.h>
# include <stdlib.h>
# include <sotypes.h>
# include <solibft.h>
# include <solibft/sostdlib.h>
# include <sothread.h>

typedef struct s_philo
{
	int			loop;
	t_sotasks	**tasks;
}	t_philo;

int	print_died(long time, int id, t_sothsync *sync);
int	routine(t_sothread *thread, t_philo *philo);
int	print_sleep_start(long time, t_sotask *task,
		t_philo *philo, t_sothread *thread);
int	print_eat_end(long time, t_sotask *task,
		t_philo *philo, t_sothread *thread);
int	print_think_start(long time, t_sotask *task,
		t_philo *philo, t_sothread *thread);

#endif