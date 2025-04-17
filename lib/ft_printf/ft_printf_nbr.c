/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_nbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:03:37 by daniefe2          #+#    #+#             */
/*   Updated: 2024/11/26 15:33:49 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_nbr(int nbr)
{
	int	digit_counter;

	digit_counter = 0;
	if (nbr == INT_MIN)
		return (ft_printf_str("-2147483648"));
	else if (nbr < 0)
	{
		digit_counter += ft_printf_char('-');
		nbr *= -1;
	}
	if (nbr > 9)
		digit_counter += ft_printf_nbr(nbr / 10);
	digit_counter += ft_printf_char((nbr % 10) + 48);
	return (digit_counter);
}
