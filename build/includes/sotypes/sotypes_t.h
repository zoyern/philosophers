/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sotypes_t.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 21:27:45 by marvin            #+#    #+#             */
/*   Updated: 2024/07/11 20:06:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOTYPES_T_H
# define SOTYPES_T_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# define TRUE 1
# define FALSE 0

typedef struct s_solib			t_solib;
typedef struct s_somemory		t_somemory;
typedef struct s_somemdata		t_somemdata;
typedef struct s_sofuncs		t_sofuncs;
typedef struct s_sotasks		t_sotasks;
typedef struct s_sotask			t_sotask;
typedef struct s_solibft		t_solibft;
typedef struct s_sotime			t_sotime;
typedef struct s_so				t_so;

typedef struct s_somemdata
{
	void		*ptr;
	t_somemdata	*next;
}	t_somemdata;

typedef struct s_somemory
{
	t_somemdata	*first;
	void		(*show)(t_solib *solib);
	t_somemdata	*(*remove)(t_solib *solib, void *ptr);
	void		(*clear)(t_solib *solib);
	void		(*add)(t_solib *solib, void *ptr);
	void		(*close)(t_solib *solib);
}	t_somemory;

typedef struct s_sotask
{
	unsigned long	id;
	long			time;
	int				start;
	int				work;
	int				end;
	t_sotask		*next;
	void			*data;
	int				(*callback)();
}	t_sotask;

typedef struct s_sotasks
{
	int			loop;
	int			count;
	long		starting;
	t_sotask	*current;
	t_sotask	*first;
}	t_sotasks;

typedef struct s_soenv
{
	char	*name;
	int		argc;
	char	**argv;
	char	**envp;
}	t_soenv;

typedef struct s_solib
{
	t_somemory	*memory;
	t_soenv		*env;
	t_sofuncs	*funcs;
	int			(*close)(t_solib *solib, int state);
	void		*(*malloc)(t_solib *solib, size_t size);
	int			(*free)(t_solib *solib, void *ptr);
	int			(*print)(const char *str, ...);
	t_solibft	*libft;
	t_sotime	*time;
	t_so		*so;
}	t_solib;

#endif