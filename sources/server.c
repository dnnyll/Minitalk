/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 11:13:25 by daniefe2          #+#    #+#             */
/*   Updated: 2025/05/16 08:52:53 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// Reconstructs characters bit by bit from SIGUSR1 (1) and SIGUSR2 (0) signals.
// Stores the current character in `current_char` and shifts bits into it.
// When 8 bits are received, prints the character (or \n if END_TRANSMISSION).
// Uses `info->si_pid` to send an ack (SIGUSR1 or SIGUSR2) back to the client.

void	handle_signal(int signal, siginfo_t *info, void *context)
{
	static unsigned char	current_char;
	static int				bit_index;

	(void)context;
	current_char |= (signal == SIGUSR1);
	bit_index++;
	if (bit_index == 8)
	{
		if (current_char == END_TRANSMISSION)
			ft_printf("\n");
		else
			ft_printf("%c", current_char);
		bit_index = 0;
		current_char = 0;
	}
	else
		current_char <<= 1;
	if (signal == SIGUSR1)
		kill(info->si_pid, SIGUSR1);
	else if (signal == SIGUSR2)
		kill(info->si_pid, SIGUSR2);
}
// Sets up SIGUSR1 and SIGUSR2 handlers using sigaction with SA_SIGINFO for extra data.
// The handler is set to handle_signal, allowing us to decode incoming bits from clients.
// sigemptyset ensures no signals are blocked during handling.
// The server prints its PID so clients know where to send data.
// The infinite pause() loop waits for signals and processes them one at a time.

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = &handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	ft_printf("%d\n", getpid());
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}