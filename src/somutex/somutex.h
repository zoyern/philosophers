/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 20:22:15 by marvin            #+#    #+#             */
/*   Updated: 2024/04/07 20:22:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOMUTEX_H
# define SOMUTEX_H

# include <sothread/all.h>

int	mutex_get_value(t_mutex mutex);
int	mutex_set_value(t_mutex mutex, int *value);
t_mutex	new_mutex(t_solib *solib, int locked, int value);
t_mutex	*new_mutexs(t_solib *solib, int nbr, int locked, int value);
int	mutex(t_mutex mutex, int (*callback)(), void *data);

#endif
