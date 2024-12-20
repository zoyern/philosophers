/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almounib <almounib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 21:32:42 by marvin            #+#    #+#             */
/*   Updated: 2024/05/16 14:44:23 by almounib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALL_H
# define ALL_H

# include <sothread/sothread_t.h>
# include <sothread.h>
# include <sothread/sosync.h>
# include <sothread/somutex.h>

void	*sothread_routine(void *arg);

#endif