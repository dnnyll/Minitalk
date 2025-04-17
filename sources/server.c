/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 11:13:25 by daniefe2          #+#    #+#             */
/*   Updated: 2025/04/17 11:48:23 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// Prints characters from the linked list, then frees each node.
// Iterates over nodes, writes their buffers to stdout, and frees them.
void	add_char_to_buffer(unsigned char c)
{
	static t_node	*head = NULL;

	if (c == '\0')
	{
		buffer_print_and_free(head);
		head = NULL;
	}
	else
		head = buffer_store_char(head, c);
}

// Prints the buffer contents and free each node in the linked list.
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

// Stores a character in a linked list node's buffer.
// Creates new nodes if we have reached the limits of the buffer_size.
t_node	*buffer_store_char(t_node *head, unsigned char c)
{
	static t_node	*current = NULL;
	t_node			*new;

	if (!head)
	{
		head = create_node();
		current = head;
		if (!head)
			return (NULL);
	}
	current->buffer[current->index++] = c;
	if (current->index == BUFFER_SIZE)
	{
		new = create_node();
		if (!new)
			return (head);
		current->next = new;
		current = new;
	}
	return (head);
}

// Signal handler that receives bits and builds characters from signals.
void	bit_to_char_handler(int signum, siginfo_t *info, void *context)
{
	static int				bit_tracker = 0;
	static unsigned char	c = 0;

	(void)context;
	if (signum == SIGUSR2)
		c |= (1 << (7 - bit_tracker));
	bit_tracker++;
	if (bit_tracker == 8)
	{
		add_char_to_buffer(c);
		bit_tracker = 0;
		c = 0;
		kill(info->si_pid, SIGUSR1);
	}
}

int	main(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = bit_to_char_handler;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		perror("sigaction SIGUSR1");
		exit(EXIT_FAILURE);
	}
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		perror("sigaction SIGUSR2");
		exit(EXIT_FAILURE);
	}
	ft_printf("Hello and welcome to Minitalk!\n");
	ft_printf("The server is up and running.\n");
	ft_printf("Please use the following PID: %d\n", getpid());
	while (1)
		pause();
	return (0);
}
