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
# include <fcntl.h>
# include <solibft.h>
# include <sotime.h>

typedef struct s_data
{
	t_sotimer test;
	t_sotimer test2;
}	t_data;

long	getCurrentTimeInMillis();

#endif