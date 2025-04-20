/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:21:32 by daniefe2          #+#    #+#             */
/*   Updated: 2024/11/28 12:31:15 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h" 

int	ft_hex_address(unsigned long long nbr)
{
	char	*base_16;
	int		size;

	base_16 = "0123456789abcdef";
	size = 0;
	if (nbr >= 16)
	{
		size += ft_hex_address(nbr / 16);
		if (size == -1)
			return (-1);
	}
	if (ft_printf_char(base_16[nbr % 16]) == -1)
		return (-1);
	size++;
	return (size);
}

int	ft_printf_ptr(void *ptr)
{
	int	size;

	if (ptr == NULL)
	{
		if (ft_printf_str("0x0") == -1)
			return (-1);
		return (3);
	}
	if (ft_printf_str("0x") == -1)
		return (-1);
	size = ft_hex_address((unsigned long long)ptr);
	if (size == -1)
		return (-1);
	return (size + 2);
}
