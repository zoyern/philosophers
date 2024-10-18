/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 21:32:42 by marvin            #+#    #+#             */
/*   Updated: 2024/09/26 21:27:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALL_H
# define ALL_H

# include <sotypes/sotypes_t.h>
# include <sotypes.h>
# include <sotypes/somemory.h>
# include <sotypes/soenv.h>
# include <sotypes/soprintf.h>
# include <sotypes/solib_utils.h>

int	solib_close(t_solib *solib, int status);

#endif