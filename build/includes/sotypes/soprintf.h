/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   soprintf.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 01:57:56 by marvin            #+#    #+#             */
/*   Updated: 2024/09/28 22:56:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOPRINTF_H
# define SOPRINTF_H
# define COLOR_OPTIONS "cbdipfsrm"

# include <sotypes/all.h>

size_t	soprintf_select(int fd, va_list list_arg, const char **str,
			size_t *len);
int		ft_printf(int fd, const char *str, va_list args);
void	soprintf_putcolor_len(int fd, const char **s, va_list list_arg,
			size_t *len);
void	ft_putchar_len(int fd, char c, size_t *len);
void	ft_putstr_len(int fd, char *s, size_t *len);
void	ft_putstrs_len(int fd, char **strs, size_t *len);
void	ft_putbool_len(int fd, int boolean, size_t *len);
void	ft_putnbr_len(int fd, long long n, size_t *len);
void	ft_putnbr_len_base(int fd, unsigned long long n, char *base,
			size_t *len);
void	ft_putptr_len(int fd, unsigned long n, char *base, size_t *len);
int		read_color(const char *color);

#endif
