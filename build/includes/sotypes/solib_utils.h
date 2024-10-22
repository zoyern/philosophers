/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solib_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 01:57:56 by marvin            #+#    #+#             */
/*   Updated: 2024/10/22 17:50:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLIB_UTILS_H
# define SOLIB_UTILS_H

# include <sotypes/all.h>

size_t		solib_strlen(const char *str);
int			solib_strcmp(const char *s1, const char *s2, size_t n);
int			hex_c_to_int(char hex_char);
int			split_color(int color, int *r, int *g, int *b);
void		solib_strmcat(char **dst, char *src);
char		*solib_strchr(const char *str, int c);
void		set_bit(int *number, int bit, int index);
int			get_bit(int number, int index);
int			set_option(const char *in, int *options);
int			check_c_in_str(const char **s, char c_in, char c_out, int *count);
int			read_hex_to_int(const char *color);
long long	solib_atoi(const char *nptr);

#endif
