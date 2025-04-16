/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 11:13:25 by daniefe2          #+#    #+#             */
/*   Updated: 2025/04/16 16:07:28 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// Prints characters from the linked list, then frees each node.
// Iterates over nodes, writes their buffers to stdout, and frees them.
void	buffer_print_and_free(void)
{
	// THERES A PROBLEM HERE< setting head to null doesnt make sense|
	// need to build a structure to make sure that we can communicate between 
	// functions, this static heads are causing problems
	static t_node	*head = NULL;
	t_node			*tmp;
	t_node			*to_free;
	ft_printf("buffer_print\n");

	tmp = head;
	ft_printf("temp: %s\n",tmp);
	while (tmp)
	{
		ft_printf("inside print loop\n");
		write(1, tmp->buffer, tmp->index);
		to_free = tmp;
		tmp = tmp->next;
		free(to_free);
	}
	write(1, "\n", 1);
	head = NULL;
}

// Stores received char in a linked list buffer.
// Allocates first node if needed, adds char to current node.
// If current node is full, creates and moves to a new node.
void	buffer_store_char(unsigned char c)
{
	static t_node	*head = NULL;
	static t_node	*current = NULL;
	t_node			*new;

	if (!head)
	{
		head = create_node();
		current = head;
		if (!head)
			return ;
	}
	current->buffer[current->index++] = c;
	if (current->index == BUFFER_SIZE)
	{
		new = create_node();
		if (!new)
			return ;
		current->next = new;
		current = new;
	}
}

// Checks if we are at the end of our input message.
// If not calls buffer_store_char.
void	add_char_to_buffer(unsigned char c)
{
	if (c == '\0')
	{
		ft_printf("NULL\n");
		buffer_print_and_free();
	}	
	else
	{
		ft_printf("storing characters\n");
		buffer_store_char(c);
	}
}

void	sig_handle(int signum, siginfo_t *info, void *context)
{
	static int				bit_tracker = 0;
	static unsigned char	c = 0;

	// (void)info;
	(void)context;
	if (signum == SIGUSR2)
		c |= (1 << (7 - bit_tracker));
	bit_tracker++;
	if (bit_tracker == 8)
	{
		ft_printf("c: %c\n", c);
		add_char_to_buffer(c);
		bit_tracker = 0;
		c = 0;
		kill(info->si_pid, SIGUSR1);
	}
	
}

int	main(void)
{
	struct sigaction sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = sig_handle;
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
	ft_printf("The server is up and running. Its PID is: %d\n", getpid());
	while (1)
		pause();
	return (0);
}
