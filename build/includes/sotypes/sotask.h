/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sotask.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:51:10 by marvin            #+#    #+#             */
/*   Updated: 2024/10/21 14:51:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOTASK_H
# define SOTASK_H

# include <sotypes/all.h>

void	sotask_change_state(t_sotask *sotask, int start, int work, int end);
void	sotask_start(long time, t_sotasks *tasks, void *data);
void	sotask_work(long time, t_sotasks *tasks, void *data);
int		sotask_end(long time, t_sotasks *tasks, void *data);

#endif