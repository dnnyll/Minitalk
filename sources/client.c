/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 11:15:47 by daniefe2          #+#    #+#             */
/*   Updated: 2025/04/19 11:31:32 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	server_confirm_reception = 0;

// Signal handler for acknowledgment from the server.
// Sets a global flag when SIGUSR1 is received to indicate message was received.
void	sig_handler(int sig)
{
	if (sig == SIGUSR1)
	{
		ft_printf("message received\n");
		server_confirm_reception = 1;
	}
}

// Converts a numeric string to an integer (PID).
// Returns the corresponding integer.
int	ft_atoi(char *str)
{
	long	nb;
	int		len;
	int		i;

	len = 0;
	while (str && str[len])
		len++;
	i = 0;
	nb = 0;
	while (i < len)
		nb = (nb * 10) + (str[i++] - '0');
	return (nb);
}

// Sends a single bit to the server using SIGUSR1 (for 0) or SIGUSR2 (for 1).
// Pauses briefly after sending to ensure the server can process the signal.
void	send_bit(pid_t pid, int bit)
{
	if (bit == 0)
	{
		if (kill(pid, SIGUSR1) == -1)
		{
			perror("Error sending SIGUSR1");
			exit (1);
		}
	}
	else
	{
		if (kill(pid, SIGUSR2) == -1)
		{
			perror("Error sending SIGUSR2");
			exit(1);
		}
	}
	usleep(200);
}

// Sends a message to the server bit by bit.
// Converts each character to binary and sends its bits using signals.
// Ends the message with a null character ('\0').
void	send_message(char *message, pid_t pid)
{
	int				bit_tracker;
	int				bit;
	int				i;
	unsigned char	c;

	bit_tracker = 0;
	while (message[bit_tracker] != '\0')
	{
		c = message[bit_tracker];
		i = 7;
		while (i >= 0)
		{
			bit = (c >> i--) & 1;
			send_bit(pid, bit);
		}
		bit_tracker++;
	}
	c = (unsigned char) '\0';
	i = 7;
	while (i >= 0)
	{
		bit = (c >> i--) & 1;
		send_bit(pid, bit);
	}
}

// Parses arguments, sets up signal handler, validates PID,
// sends message to server.
// Waits for acknowledgment signal before exiting.
int	main(int argc, char **argv)
{
	pid_t	pid;
	char	*message;

	if (argc != 3)
		return (ft_printf("Usage: %s <server_pid> <message>\n", argv[0]), 1);
	else
	{
		if (signal(SIGUSR1, sig_handler) == SIG_ERR)
		{
			ft_printf("Error with sig_handler() !\n");
			exit(0);
		}
		pid = ft_atoi(argv[1]);
		if (pid < 2 || pid > 4194304)
			return (ft_printf("The PID is invalid. \n"), 1);
		message = argv[2];
		send_message(message, pid);
		while (!server_confirm_reception)
			pause();
		ft_printf("Acknowledgment received.\n");
		ft_printf("Message sent successfully to pid : %d\n.", pid);
		return (0);
	}
}
