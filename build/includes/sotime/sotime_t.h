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

#ifndef SOTIME_T_H
# define SOTIME_T_H

# include <unistd.h>
# include <stdlib.h>
# include <sotypes.h>
# include <solibft.h>

typedef struct s_sotime	t_sotime;

typedef	struct s_sotimer
{
	int		start;
	int		working;
	int		finish;
	long	start_millis;
	long	millis;
}	t_sotimer;


typedef struct s_sotime
{
	int					loop;
	long				starting_time;
	long				current;
	long				millis;
	int					(*close)(t_so *so, int state);
	int					(*update)(t_sotime *sotime);

}	t_sotime;

#endif