# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/02 10:53:48 by daniefe2          #+#    #+#              #
#    Updated: 2025/04/17 11:03:21 by daniefe2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minitalk

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -g3 -I./headers

GREEN	= \033[0;32m
RED		= \033[0;31m
YELLOW	= \033[0;33m
BLUE	= \033[0;34m
CYAN	= \033[0;36m
RESET	= \033[0m

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
			@echo "$(GREEN)Client compiled successfully.$(RESET)"

$(SERVER):	$(SERVER_SRC) $(FT_PRINTF)
			@$(CC) $(CFLAGS) -o $(SERVER) $(SERVER_SRC) -L$(FT_PRINTF_DIR) -lftprintf
			@echo "$(GREEN)Server compiled successfully.$(RESET)"

$(NAME):	$(SERVER) $(CLIENT)
			@echo "$(GREEN)All targets built successfully!$(RESET)"

clean:
			@make -C $(FT_PRINTF_DIR) clean
			@rm -f *.o
			@echo "$(CYAN)Cleaned up object files.$(RESET)"

fclean:		clean
			@rm -f $(CLIENT) $(SERVER) $(FT_PRINTF)
			@echo "$(CYAN)Full clean completed.$(RESET)"

re:			fclean all
			@echo "$(CYAN)Rebuilt everything from scratch.$(RESET)"

.PHONY: all clean fclean re
