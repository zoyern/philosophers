/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sotypes.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:59:30 by marvin            #+#    #+#             */
/*   Updated: 2024/09/28 20:21:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOTYPES_H
# define SOTYPES_H

# include <sotypes/sotypes_t.h>

t_solib	*sonew_types(int argc, char **argv, char **envp);
void	*somalloc(t_solib *solib, size_t size);
int		sofree(t_solib *solib, void *ptr);
int		solib_close(t_solib *solib, int status);
int		soprintf(const char *str, ...);
int		soprintf_fd(int fd, const char *str, ...);
char	*soprintf_get(t_solib *solib, const char *str, ...);
int		solib_close(t_solib *solib, int status);

#endif