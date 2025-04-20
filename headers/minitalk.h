/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 09:24:45 by daniefe2          #+#    #+#             */
/*   Updated: 2025/04/19 11:32:36 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include "../lib/ft_printf/ft_printf.h"

# define BUFFER_SIZE 1024

typedef struct s_node
{
	unsigned char			buffer[BUFFER_SIZE];
	size_t					index;
	struct s_node			*next;
}	t_node;

//	-=	server.c			//////////////////////////////////////////////
void		bit_to_char_handler(int signum, siginfo_t *info, void *context);
t_node		*store_char_in_buffer(t_node *head, unsigned char c);
void		buffer_print_and_free(t_node *head);
void		add_char_to_buffer(unsigned char c, pid_t pid);

//	-=	client.c			//////////////////////////////////////////////
void		send_message(char *message, pid_t pid);
void		send_bit(pid_t pid, int bit);
int			ft_atoi(char *str);
void		sig_handler(int sig);
//	-=	utils.c			//////////////////////////////////////////////
t_node		*create_node(void);

#endif