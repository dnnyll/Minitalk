/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:58:46 by daniefe2          #+#    #+#             */
/*   Updated: 2025/04/17 11:48:43 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// Creates a new node for the linked list used in buffering characters.
// Initializes index to 0 and next to NULL. Returns the new node.
t_node	*create_node(void)
{
	t_node	*node;

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
