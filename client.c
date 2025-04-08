/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 11:15:47 by daniefe2          #+#    #+#             */
/*   Updated: 2025/04/03 11:16:53 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// Function to convert string to integer (PID)
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

// Function to send a signal for each bit of a character
void	ft_send_signal(int pid, char c)
{
	int	bit;
	int	i;

	i = 7;
	while (i >= 0)
	{
		// Extract bit (0 or 1) from character
		bit = (c >> i) & 1;
		if (bit == 0)
			kill(pid, SIGUSR1); // Send SIGUSR1 for 0
		else
			kill(pid, SIGUSR2); // Send SIGUSR2 for 1
		usleep(100);  // Delay to ensure signal is processed
		i--;
	}
}

int	main(int argc, char **argv)
{
	int	pid;

	// Check for the correct number of arguments
	if (argc != 3)
	{
		write(1, "Args error\n", 11);
		return (1);
	}

	// Convert PID string to integer
	pid = ft_atoi(argv[1]);
	while (argv[2] && *argv[2])
	{
		// Send each character in the string as signals
		ft_send_signal(pid, *argv[2]++);
	}
	// Send a newline character to the server
	ft_send_signal(pid, '\n');
	return (0);
}
