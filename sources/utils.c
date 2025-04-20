/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:58:46 by daniefe2          #+#    #+#             */
/*   Updated: 2025/04/19 10:40:17 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
	// No initialization of buffer - it's not strictly necessary
	// since we'll only read up to the index we've written to
	// Creates a new node for the linked list used in buffering characters.
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

// Prints all characters from the linked list buffer to standard output.
// Frees each node in the linked list after printing.
void	buffer_print_and_free(t_node *head)
{
	t_node	*tmp;
	t_node	*to_free;

	tmp = head;
	while (tmp)
	{
		write(1, tmp->buffer, tmp->index);
		to_free = tmp;
		tmp = tmp->next;
		free(to_free);
	}
	write(1, "\n", 1);
}
