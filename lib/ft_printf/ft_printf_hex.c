/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:20:47 by daniefe2          #+#    #+#             */
/*   Updated: 2024/11/28 12:30:15 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_size_hex(unsigned int nbr)
{
	int	size;

	size = 0;
	if (nbr == 0)
		return (1);
	while (nbr)
	{
		size++;
		nbr /= 16;
	}
	return (size);
}

int	ft_printf_hex(unsigned int nbr, int hex_switch)
{
	char	*base_16;
	int		size;

	if (hex_switch == 0)
		base_16 = "0123456789ABCDEF";
	else
		base_16 = "0123456789abcdef";
	if (nbr == 0)
	{
		if (ft_printf_char('0') == -1)
			return (-1);
		return (1);
	}
	if (nbr >= 16)
	{
		if (ft_printf_hex(nbr / 16, hex_switch) == -1)
			return (-1);
	}
	if (ft_printf_char(base_16[nbr % 16]) == -1)
		return (-1);
	size = ft_size_hex(nbr);
	return (size);
}
