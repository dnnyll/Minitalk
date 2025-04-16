# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daniefe2 <daniefe2@student.42lausanne.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/02 10:53:48 by daniefe2          #+#    #+#              #
#    Updated: 2025/04/16 14:58:26 by daniefe2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minitalk

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -g3 -I./headers

SRC_DIR		=	sources
FT_PRINTF_DIR =	lib/ft_printf
FT_PRINTF	=	$(FT_PRINTF_DIR)/libftprintf.a

CLIENT		=	client
SERVER		=	server

CLIENT_SRC	=	$(SRC_DIR)/client.c $(SRC_DIR)/utils.c
SERVER_SRC	=	$(SRC_DIR)/server.c $(SRC_DIR)/utils.c

all:		$(NAME)

$(FT_PRINTF):
			@make -C $(FT_PRINTF_DIR)

$(CLIENT):	$(CLIENT_SRC) $(FT_PRINTF)
			@$(CC) $(CFLAGS) -o $(CLIENT) $(CLIENT_SRC) -L$(FT_PRINTF_DIR) -lftprintf

$(SERVER):	$(SERVER_SRC) $(FT_PRINTF)
			@$(CC) $(CFLAGS) -o $(SERVER) $(SERVER_SRC) -L$(FT_PRINTF_DIR) -lftprintf

$(NAME):	$(SERVER) $(CLIENT)

clean:
			@make -C $(FT_PRINTF_DIR) clean
			@rm -f *.o

fclean:		clean
			@rm -f $(CLIENT) $(SERVER) $(FT_PRINTF)

re:			fclean all

.PHONY: all clean fclean re
