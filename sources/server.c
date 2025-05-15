/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 11:13:25 by daniefe2          #+#    #+#             */
/*   Updated: 2025/05/08 19:39:05 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// // Sends an acknowledgment signal (SIGUSR1) to the client to confirm reception.
// // Called after the full message has been received (null character).
// static void	signal_confirmation(pid_t server_pid)
// {
// 	if (kill(server_pid, SIGUSR1) == -1)
// 	{
// 		perror("Error confirming message SIGUSR1");
// 		exit (1);
// 	}
// }

// // Adds a received character to a buffer (linked list).
// // If the character is the null terminator, prints and frees the full buffer,
// // then sends acknowledgment to the client.
// void	add_char_to_buffer(unsigned char c, pid_t server_pid)
// {
// 	static t_node	*head = NULL;

// 	if (c == '\0')
// 	{
// 		buffer_print_and_free(head);
// 		head = NULL;
// 		signal_confirmation(server_pid);
// 	}
// 	else
// 		head = store_char_in_buffer(head, c);
// }

// // Stores a character into a node's buffer in the linked list.
// // If the current buffer is full, creates a new node and continues storing.
// t_node	*store_char_in_buffer(t_node *head, unsigned char c)
// {
// 	static t_node	*current = NULL;
// 	t_node			*new;

// 	if (!head)
// 	{
// 		head = create_node();
// 		current = head;
// 		if (!head)
// 			return (NULL);
// 	}
// 	current->buffer[current->index++] = c;
// 	if (current->index == BUFFER_SIZE)
// 	{
// 		new = create_node();
// 		if (!new)
// 			return (head);
// 		current->next = new;
// 		current = new;
// 	}
// 	return (head);
// }

// /*
// info is a pointer to a siginfo_t struct. 
// It's filled in by the kernel automatically whenever the signal handler is 
// triggered with SA_SIGINFO,and it contains detailed information about the signal 
// — including who sent it (si_pid = process that sent the signal).
// */
// // Signal handler to reconstruct characters from bits received via signals.
// // Collects 8 bits into a character and adds it to the buffer.
// // Once a full character is received, it’s passed to `add_char_to_buffer`.
// void	bit_to_char_handler(int signum, siginfo_t *info, void *context)
// {
// 	static int				bit_tracker = 0;
// 	static unsigned char	c = 0;
// 	pid_t					client_pid;

// 	(void)context;
// 	client_pid = info->si_pid;
// 	if (signum == SIGUSR2)
// 		c |= (1 << (7 - bit_tracker));
// 	bit_tracker++;
// 	if (bit_tracker == 8)
// 	{
// 		add_char_to_buffer(c, client_pid);
// 		bit_tracker = 0;
// 		c = 0;
// 	}
// }

// /*
//  struct sigaction {
//                void     (*sa_handler)(int);
//                void     (*sa_sigaction)(int, siginfo_t *, void *);
//                sigset_t   sa_mask;
//                int        sa_flags; =SIGINFO
//                void     (*sa_restorer)(void);
//            };
// */
// // Main function of the server.
// // Prints server PID, sets up signal handlers
// // and waits indefinitely for signals.
// // Handles SIGUSR1 and SIGUSR2 using `sigaction`.
// //
// // sa.sa_flags = SA_SIGINFO; // allows you to use a three argument sigaction
// // function.
// // 
// // sigaction is used to define how the program should behave when it 
// // receives a specific signal (like SIGUSR1 or SIGUSR2).
// //
// // pause(); // Just go to sleep and do nothing until a signal is received.
// int	main(void)
// {
// 	struct sigaction	sa;
// 	pid_t				server_pid;

// 	server_pid = getpid();
// 	ft_ft_ft_printf("Hello and welcome to Minitalk!\n");
// 	ft_ft_ft_printf("The server is up and running.\n");
// 	ft_ft_ft_printf("Please use the following PID: %d\n", server_pid);
// 	sa.sa_flags = SA_SIGINFO;
// 	sa.sa_sigaction = bit_to_char_handler;
// 	sigemptyset(&sa.sa_mask);
// 	if (sigaction(SIGUSR1, &sa, NULL) == -1)
// 	{
// 		perror("sigaction SIGUSR1");
// 		exit(EXIT_FAILURE);
// 	}
// 	if (sigaction(SIGUSR2, &sa, NULL) == -1)
// 	{
// 		perror("sigaction SIGUSR2");
// 		exit(EXIT_FAILURE);
// 	}
// 	while (1)
// 		pause();
// 	return (0);
// }


//----------------------------------------------------------------------

// int	store_char(char current_char, t_data *data)
// {
// 	char	*storage = 0;
// 	int	i = 0;	
// 	while (i <= data->input_length)
// 	{
// 		storage[i] = current_char;
// 		if (storage[i] == '\0')
// 			return (0);
// 		i++;
// 	}
// 	return (1);
	
// }
/*
The siginfo_t argument to a SA_SIGINFO handler
       When the SA_SIGINFO flag is specified in act.sa_flags, the signal handler address is passed via the act.sa_sigaction field.  This handler takes three arguments, as follows:

           void
           handler(int sig, siginfo_t *info, void *ucontext)
           {
               ...
           }

       These three arguments are as follows

       sig    The number of the signal that caused invocation of the handler.

       info   A pointer to a siginfo_t, which is a structure containing further information about the signal, as described below.

       ucontext
              This  is a pointer to a ucontext_t structure, cast to void *.  The structure pointed to by this field contains signal context information that was saved on the user-space stack by the kernel;
              for details, see sigreturn(2).  Further information about the ucontext_t structure can be found in getcontext(3) and signal(7).  Commonly, the handler function doesn't make  any  use  of  the
              third argument.
*/














void handler(int signum, siginfo_t *info, void *context)
{
	// sa.siginfo	si_pid;
    static unsigned char current_char = 0;
    static int bit_pos = 7;
    static char message[50000];  // A buffer to store the incoming message
    static int msg_index = 0;   // Index for the message buffer
    (void)context;  // Unused

    // Print debug information for incoming signals
    if (signum == SIGUSR1)
    {
        // Bit 0 (SIGUSR1)
        // ft_printf("Received SIGUSR1 (bit 0)\n");
        current_char &= ~(1 << bit_pos);  // Clear the bit at bit_pos
		// store_char(current_char);
    }
    else if (signum == SIGUSR2)
    {
        // Bit 1 (SIGUSR2)
        // ft_printf("Received SIGUSR2 (bit 1)\n");
        current_char |= (1 << bit_pos);  // Set the bit at bit_pos
    }

    // Move to the next bit position
    bit_pos--;

    // If all bits of the character have been received
    if (bit_pos < 0)
    {
        // Check for null character to mark end of the message
        if (current_char == '\0')
        {
            // Print the full message and reset
            // ft_printf("Message received: %s\n", message);
            write(1, message, msg_index);  // Print the message
            write(1, "\n", 1);  // New line after the message

            // Reset the message buffer and index for the next message
            msg_index = 0;
            message[0] = '\0';
        }
        else
        {
            // Store the received character in the message buffer
            message[msg_index] = current_char;
            msg_index++;

            // Ensure we don't go beyond the buffer size
            if (msg_index >= 50000 - 1)
            {
                ft_printf("Message buffer full!\n");
                msg_index = 0;  // Reset buffer index to avoid overflow
            }
        }

        // Reset for the next character
        bit_pos = 7;
        current_char = 0;
    }

    // Send acknowledgment back to the client (SIGUSR1)
    kill(info->si_pid, SIGUSR1);
}


int main(void)
{
	struct sigaction sa;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler;
	pid_t	pid_server = getpid();
	sigemptyset(&sa.sa_mask);

	// Register SIGUSR1 and SIGUSR2 signals for receiving data
	if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		perror("sigaction");
		return 1;
	}

	// Print the server PID for the client to know where to send the signals
	ft_printf("Server PID: %d\n", pid_server);

	// The server will keep running to receive signals
	while (1)
		pause();  // Wait for signals
}
