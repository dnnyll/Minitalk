/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:58:46 by daniefe2          #+#    #+#             */
/*   Updated: 2025/04/16 12:00:49 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_node	*create_node(void)
{
	t_node *node;
	node = malloc(sizeof(t_node));
	if (!node)
	{
		ft_printf("Error allocating node.\n");
		return (NULL);
	}
	node->index = 0;
	node->next = NULL;
	return (node);
}