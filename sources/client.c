/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 11:15:47 by daniefe2          #+#    #+#             */
/*   Updated: 2025/04/17 11:45:55 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_ack_received = 0;

// Signal handler for acknowledgment. 
// Sets the global flag `g_ack_received` to 1 when SIGUSR1 is received.
void	sig_handler(int sig)
{
	if (sig == SIGUSR1)
		g_ack_received = 1;
}

// Converts string to integer (PID)
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
void	send_bit(int pid, int bit)
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
	usleep(100);
}

// Sends a message to the server bit by bit.
// Each character in the string is converted to binary and sends via signals.
void	send_message(char *message, int pid)
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

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	int					pid;
	char				*message;

	if (argc != 3)
	{
		ft_printf("Usage: %s <server_pid> <message>\n", argv[0]);
		return (1);
	}
	sa = (struct sigaction){0};
	sa.sa_handler = sig_handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGUSR1, &sa, NULL);
	pid = ft_atoi(argv[1]);
	message = argv[2];
	send_message(message, pid);
	while (!g_ack_received)
		pause();
	ft_printf("Acknowledgment received.\n");
	ft_printf("Your message has been successfully sent to pid : %d\n.", pid);
	return (0);
}
