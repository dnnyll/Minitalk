# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/02 10:53:48 by daniefe2          #+#    #+#              #
#    Updated: 2025/04/03 11:13:08 by daniefe2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minitalk

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -g3 -I./headers

CLIENT	=	client
SERVER	=	server

all:		$(NAME)

$(SERVER):	$(SERVER).c minitalk.h
			@$(CC) $(CFLAGS) -o $(SERVER) $(SERVER).c

$(CLIENT):	$(CLIENT).c minitalk.h
			@$(CC) $(CFLAGS) -o $(CLIENT) $(CLIENT).c

$(NAME):	$(SERVER) $(CLIENT)

clean:
			@$(RM) $(CLIENT) $(SERVER)

fclean:		clean

re:			fclean all

.PHONY: 	all clean fclean re