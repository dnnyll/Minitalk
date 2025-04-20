/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 11:12:30 by daniefe2          #+#    #+#             */
/*   Updated: 2024/11/26 14:59:20 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>
# include <stdarg.h>
# include <limits.h>
# include <stdio.h>

int		ft_printf_char(int c);
int		ft_printf_str(char *s);
int		ft_printf_ptr(void *ptr);
int		ft_printf_unint(unsigned int nbr);
int		ft_printf_nbr(int nbr);
int		ft_printf_hex(unsigned int nbr, int hex_switch);
int		ft_printf(const char *s, ...);
void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(const char *s);
void	ft_putchar_fd(char c, int fd);

#endif