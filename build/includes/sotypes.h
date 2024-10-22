/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sotypes.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:59:30 by marvin            #+#    #+#             */
/*   Updated: 2024/10/22 18:04:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOTYPES_H
# define SOTYPES_H

# include <sotypes/sotypes_t.h>

t_solib		*sonew_types(int argc, char **argv, char **envp);
void		*somalloc(t_solib *solib, size_t size);
int			sofree(t_solib *solib, void *ptr);
int			solib_close(t_solib *solib, int status);
int			soprintf(const char *str, ...);
int			soprintf_fd(int fd, const char *str, ...);
int			solib_close(t_solib *solib, int status);
t_sotask	*sonew_task(t_solib *solib, char *time, int (*callback)(),
				void *data);
t_sotasks	*sotask_list(t_solib *solib);
void		sotask_add(t_sotasks *list, unsigned long id, t_sotask *task);
int			sotask(long time, t_sotasks *tasks, void *data);

#endif