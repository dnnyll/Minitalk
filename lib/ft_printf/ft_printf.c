/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 14:39:53 by daniefe2          #+#    #+#             */
/*   Updated: 2024/11/26 15:28:37 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int	ft_process_input(const char *input, unsigned int *i, va_list *args)
{
	unsigned int	return_counter;

	return_counter = 0;
	if (input[*i] == 'c')
		return_counter += ft_printf_char(va_arg(*args, int));
	else if (input[*i] == 's')
		return_counter += ft_printf_str(va_arg(*args, char *));
	else if (input[*i] == 'p')
		return_counter += ft_printf_ptr(va_arg(*args, void *));
	else if (input[*i] == 'd' || input[*i] == 'i')
		return_counter += ft_printf_nbr(va_arg(*args, int));
	else if (input[*i] == 'x')
		return_counter += ft_printf_hex(va_arg(*args, int), 1);
	else if (input[*i] == 'X')
		return_counter += ft_printf_hex(va_arg(*args, int), 0);
	else if (input[*i] == 'u')
		return_counter += ft_printf_unint(va_arg(*args, int));
	else if (input[*i] == '%')
	{
		ft_printf_char('%');
		return (1);
	}
	return (return_counter);
}

int	ft_printf(const char *input, ...)
{
	va_list			args;
	unsigned int	i;
	unsigned int	return_len;

	i = 0;
	return_len = 0;
	va_start(args, input);
	while (input[i])
	{
		if (input[i] == '%')
		{
			i++;
			return_len += ft_process_input(input, &i, &args);
		}
		else
		{
			return_len += ft_printf_char(input[i]);
		}
		i++;
	}
	va_end(args);
	return (return_len);
}
