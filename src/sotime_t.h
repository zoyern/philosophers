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

typedef struct s_sotime
{
	int					loop;
	int					(*close)(t_so *so, int state);

}	t_sotime;

#endif