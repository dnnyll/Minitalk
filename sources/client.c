/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 11:15:47 by daniefe2          #+#    #+#             */
/*   Updated: 2025/05/16 09:01:09 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_signal(int pid, unsigned char character)
{
	int				bit_index;
	unsigned char	temp_char;

	bit_index = 8;
	temp_char = character;
	while (bit_index > 0)
	{
		bit_index--;
		temp_char = character >> bit_index;
		if (temp_char % 2 == 0)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(200);
	}
}

void	handle_read_receipt(int signal)
{
	static int	bit_count = 0;
	static int	char_count = 0;
	static unsigned char current_char = 0;

	if (signal == SIGUSR1)
		current_char |= (1 << (7 - bit_count));
	bit_count++;
	if (bit_count == 8)
	{
		if (current_char == '\0')
		{
			ft_printf("Reiciving: null termination\n");
			ft_printf("Total characters received: %d\n", char_count);
		}
		else
			char_count++;
		bit_count = 0;
		current_char = 0;
	}
}

int	ft_atoi(const char *str)
{
	int		i;
	int		negative;
	int		result;

	i = 0;
	negative = 1;
	result = 0;
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\t' || str[i] == '\v')
		i++;
	if (str[i] == '-')
		negative *= -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	result *= negative;
	return (result);
}
// The client sends a message to the server, bit by bit, using signals.
// Each bit is sent as SIGUSR1 (1) or SIGUSR2 (0) to the server's PID.
// The server acknowledges each bit with a signal back to the client.
// The client waits for these acknowledgments to avoid sending too fast.
// A null character '\0' is sent at the end to signal transmission is complete.

int	main(int argc, char *argv[])
{
	pid_t		server_pid;
	const char	*message;
	int			i;
	
	signal(SIGUSR1, handle_read_receipt);
	signal(SIGUSR2, handle_read_receipt);
	if (argc != 3)
	{
		ft_printf("Usage: %s <pid> <message>\n", argv[0]);
		exit(0);
	}
	server_pid = ft_atoi(argv[1]);
	message = argv[2];
	i = 0;
	while (message[i])
		send_signal(server_pid, message[i++]);
	send_signal(server_pid, '\0');
	return (0);
}