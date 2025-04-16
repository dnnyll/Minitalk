/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 09:24:45 by daniefe2          #+#    #+#             */
/*   Updated: 2025/04/16 15:03:03 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include "../lib/ft_printf/ft_printf.h"
#define BUFFER_SIZE 1024

typedef struct s_node
{
	char				buffer[BUFFER_SIZE];
	int					index;
	struct s_node		*next;
}	t_node;

//	-=	server.c			//////////////////////////////////////////////
void	sig_handle(int signum, siginfo_t *info, void *context);
void	add_char_to_buffer(unsigned char c);
void	buffer_store_char(unsigned char c);
void	buffer_print_and_free(void);

//	-=	client.c			//////////////////////////////////////////////
void	send_message(char *message, int pid);
void	send_bit(int	pid, int bit);
int		ft_atoi(char *str);
void	sig_handler(int sig);

//	-=	utils.c			//////////////////////////////////////////////
t_node	*create_node(void);

#endif