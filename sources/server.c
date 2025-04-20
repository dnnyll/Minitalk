/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 11:13:25 by daniefe2          #+#    #+#             */
/*   Updated: 2025/04/19 11:13:24 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// Sends an acknowledgment signal (SIGUSR1) to the client to confirm reception.
// Called after the full message has been received (null character).
static void	signal_confirmation(pid_t server_pid)
{
	if (kill(server_pid, SIGUSR1) == -1)
	{
		perror("Error confirming message SIGUSR1");
		exit (1);
	}
}

// Adds a received character to a buffer (linked list).
// If the character is the null terminator, prints and frees the full buffer,
// then sends acknowledgment to the client.
void	add_char_to_buffer(unsigned char c, pid_t server_pid)
{
	static t_node	*head = NULL;

	if (c == '\0')
	{
		buffer_print_and_free(head);
		head = NULL;
		signal_confirmation(server_pid);
	}
	else
		head = store_char_in_buffer(head, c);
}

// Stores a character into a node's buffer in the linked list.
// If the current buffer is full, creates a new node and continues storing.
t_node	*store_char_in_buffer(t_node *head, unsigned char c)
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

/*
info is a pointer to a siginfo_t struct. 
It's filled in by the kernel automatically whenever the signal handler is triggered with SA_SIGINFO,
and it contains detailed information about the signal — including who sent it (si_pid = process that sent the signal).

*/


// Signal handler to reconstruct characters from bits received via signals.
// Collects 8 bits into a character and adds it to the buffer.
// Once a full character is received, it’s passed to `add_char_to_buffer`.
void	bit_to_char_handler(int signum, siginfo_t *info, void *context)
{
	static int				bit_tracker = 0;
	static unsigned char	c = 0;
	pid_t					client_pid;

	(void)context;
	client_pid = info->si_pid;
	if (signum == SIGUSR2)
		c |= (1 << (7 - bit_tracker));
	bit_tracker++;
	if (bit_tracker == 8)
	{
	add_char_to_buffer(c, client_pid);
		bit_tracker = 0;
		c = 0;
	}
}


/*
 struct sigaction {
               void     (*sa_handler)(int);
               void     (*sa_sigaction)(int, siginfo_t *, void *);
               sigset_t   sa_mask;
               int        sa_flags; =SIGINFO
               void     (*sa_restorer)(void);
           };
*/
// Main function of the server.
// Prints server PID, sets up signal handlers
// and waits indefinitely for signals.
// Handles SIGUSR1 and SIGUSR2 using `sigaction`.
int	main(void)
{
	struct sigaction	sa;
	pid_t				server_pid;

	server_pid = getpid();
	ft_printf("Hello and welcome to Minitalk!\n");
	ft_printf("The server is up and running.\n");
	ft_printf("Please use the following PID: %d\n", server_pid);
	sa.sa_flags = SA_SIGINFO; // allows you to use a three argument sigaction function
	sa.sa_sigaction = bit_to_char_handler;
	sigemptyset(&sa.sa_mask);
	// sigaction is used to define how the program should behave when it receives a specific signal (like SIGUSR1 or SIGUSR2).
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
	while (1)
		pause(); // Just go to sleep and do nothing until a signal is received.
	return (0);
}
