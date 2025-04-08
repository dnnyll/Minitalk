/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 11:13:25 by daniefe2          #+#    #+#             */
/*   Updated: 2025/04/03 14:37:47 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <signal.h>

//	The server.c program listens for signals sent by the client, decodes them, and prints the message sent by the client.

// Function to print numbers (PID)
void	ft_putnbr(long nbr)
{
	char	temp;

	if (nbr / 10 > 0)
		ft_putnbr(nbr / 10);
	temp = nbr % 10 + '0';
	write(1, &temp, 1);
}

// Signal handler to reconstruct characters from bits
void	sig_handle(int signal)
{
	static int	i = 0;    // Bit count (0 to 7)
	static char	n = 0;    // Accumulated character bits

	// Shift the accumulated bits and add the new bit
	n = (n << 1) | (signal == SIGUSR2);
	i++;

	// If 8 bits have been received, print the character and reset counters
	if (i == 8)
	{
		write(1, &n, 1);  // Print the reconstructed character
		n = 0;  // Reset the bit accumulator
		i = 0;  // Reset the bit count
	}
}

int	main(void)
{
	struct sigaction	sigact;

	sigact.sa_handler = &sig_handle;
	sigact.sa_flags = SA_RESTART;
	sigaction(SIGUSR1, &sigact, 0);
	sigaction(SIGUSR2, &sigact, 0);
	write(1, "Hello and welcome to Minitalk!\n", 31);
	write(1, "The server is up and running. It's PID is: ", 43);
	ft_putnbr(getpid());
	write(1, "\n", 1);
	while (1)
		usleep(100);
	return (0);
}
