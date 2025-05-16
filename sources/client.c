/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 11:15:47 by daniefe2          #+#    #+#             */
/*   Updated: 2025/05/15 22:50:31 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// volatile sig_atomic_t	g_server_confirm_reception = 0;

// // Signal handler for acknowledgment from the server.
// // Sets a global flag when SIGUSR1 is received to indicate message was received.
// void	sig_handler(int sig)
// {
// 	if (sig == SIGUSR1)
// 	{
// 		ft_printf("message received\n");
// 		g_server_confirm_reception = 1;
// 	}
// }

// // Converts a numeric string to an integer (PID).
// // Returns the corresponding integer.
// int	ft_atoi(char *str)
// {
// 	long	nb;
// 	int		len;
// 	int		i;

// 	len = 0;
// 	while (str && str[len])
// 		len++;
// 	i = 0;
// 	nb = 0;
// 	while (i < len)
// 		nb = (nb * 10) + (str[i++] - '0');
// 	return (nb);
// }

// // Sends a single bit to the server using SIGUSR1 (for 0) or SIGUSR2 (for 1).
// // Pauses briefly after sending to ensure the server can process the signal.
// void	send_bit(pid_t pid, int bit)
// {
// 	if (bit == 0)
// 	{
// 		if (kill(pid, SIGUSR1) == -1)
// 		{
// 			perror("Error sending SIGUSR1");
// 			exit (1);
// 		}
// 	}
// 	else
// 	{
// 		if (kill(pid, SIGUSR2) == -1)
// 		{
// 			perror("Error sending SIGUSR2");
// 			exit(1);
// 		}
// 	}
// 	usleep(300);
// }

// // Sends a message to the server bit by bit.
// // Converts each character to binary and sends its bits using signals.
// // Ends the message with a null character ('\0').
// void	send_message(char *message, pid_t pid)
// {
// 	int				bit_tracker;
// 	int				bit;
// 	int				i;
// 	unsigned char	c;

// 	bit_tracker = 0;
// 	while (message[bit_tracker] != '\0')
// 	{
// 		c = message[bit_tracker];
// 		i = 7;
// 		while (i >= 0)
// 		{
// 			bit = (c >> i--) & 1;
// 			send_bit(pid, bit);
// 		}
// 		bit_tracker++;
// 	}
// 	c = (unsigned char) '\0';
// 	i = 7;
// 	while (i >= 0)
// 	{
// 		bit = (c >> i--) & 1;
// 		send_bit(pid, bit);
// 	}
// }

// // Parses arguments, sets up signal handler, validates PID,
// // sends message to server.
// // Waits for acknowledgment signal before exiting.
// int	main(int argc, char **argv)
// {
// 	pid_t	pid;
// 	char	*message;

// 	if (argc != 3)
// 		return (ft_printf("Usage: %s <server_pid> <message>\n", argv[0]), 1);
// 	else
// 	{
// 		if (signal(SIGUSR1, sig_handler) == SIG_ERR)
// 		{
// 			ft_printf("Error with sig_handler() !\n");
// 			exit(0);
// 		}
// 		pid = ft_atoi(argv[1]);
// 		if (pid < 2 || pid > 4194304)
// 			return (ft_printf("The PID is invalid. \n"), 1);
// 		message = argv[2];
// 		send_message(message, pid);
// 		while (!g_server_confirm_reception)
// 			pause();
// 		ft_printf("Acknowledgment received.\n");
// 		ft_printf("Message sent successfully to pid : %d\n.", pid);
// 		return (0);
// 	}
// }

//-----------------------------------------------------------------------------














// void ack_handler(int signum)
// {
// 	(void)signum;
// 	// Just wakes up the pause() in send_char()
// }

// void	send_char(pid_t pid, unsigned char c)
// {
// 	int	bit;

// 	bit = 7;
// 	while (bit >= 0)
// 	{
// 		send_signal(pid, (c >> bit) & 1);
// 		pause();  // wait for acknowledgment from server
// 		bit--;
// 	}
// }

// void	send_signal(pid_t pid, int bit)
// {
// 	if (bit == 0)
// 		kill(pid, SIGUSR1);  // Send SIGUSR1 for bit 1
// 	else
// 		kill(pid, SIGUSR2);  // Send SIGUSR2 for bit 0
// }
// // void	init_data(t_data *data)
// // {
// // 	int		input_length = 0;
// // 	char	*buffer = 0;
// // }

// int	main(int argc, char **argv)
// {
// 	// data = init_data;
// 	pid_t	pid_client;
// 	int		i;

// 	// assigning value to struct value is now working
// 	// declare data = init data like in FdF?

// 	struct sigaction sa_ack;
// 	sa_ack.sa_handler = ack_handler;
// 	sigemptyset(&sa_ack.sa_mask);
// 	sa_ack.sa_flags = SA_RESTART;

// 	if (argc != 3)
// 	{
// 		write(2, "Usage: ./client <PID> <message>\n", 33);
// 		return (1);
// 	}

// 	// can i verify with sigaction if the pid signal is correct so i can print an error if necessary
// 	// if (sigaction(SIGUSR1, pid) == SIG_ERR)
// 	// {
// 	// 	ft_printf("Error with sig_handler() !\n");
// 	// 	exit(0);
// 	// }

// 	if ((pid_client = (pid_t)ft_atoi_strict(argv[1])) == 1)
// 	{
// 		perror("Incorrect PID!\n");
// 		exit (EXIT_FAILURE);
// 	}

// 	// if (pid_client != pid_server)
// 	// if (pid < 2 || pid > 4194304)
// 	// {
// 	// 	write(2, "The PID is invalid.\n", 21);
// 	// 	return (1);
// 	// }

// 	if (sigaction(SIGUSR1, &sa_ack, NULL) == -1)
// 	{
// 		perror("sigaction (ACK)");
// 		exit(EXIT_FAILURE);
// 	}

// 	// Loop through the string and send each character
// 	i = 0;
// 	while (argv[2][i] != '\0')
// 	{
// 		send_char(pid_client, argv[2][i]);  // Send the character one by one
// 		i++;
// 	}

// 	// Send a null character '\0' to mark the end of the string
// 	send_char(pid_client, '\0');
// 	return (0);
// }


#include "minitalk.h"

void	send_signal(int pid, unsigned char character)
{
	int				i;
	unsigned char	temp_char;

	i = 8;
	temp_char = character;
	while (i > 0)
	{
		i--;
		temp_char = character >> i;
		if (temp_char % 2 == 0)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(420);
	}
}


void	handle_read_receipt(int signal)
{
	if (signal == SIGUSR1)
		ft_printf("Received bit 1\n");
	else if (signal == SIGUSR2)
		ft_printf("Received bit 0\n");
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