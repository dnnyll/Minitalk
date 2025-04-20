# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/16 10:37:59 by daniefe2          #+#    #+#              #
#    Updated: 2024/11/21 11:17:29by daniefe2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project-specific variables
NAME		= libftprintf.a
SRCS		=	ft_printf.c \
				ft_printf_char.c \
				ft_printf_hex.c \
				ft_printf_nbr.c \
				ft_printf_ptr.c \
				ft_printf_str.c \
				ft_printf_unint.c \
				ft_putchar_fd.c \
				ft_strlen.c \
				ft_putstr_fd.c

MAIN		= main.c

OBJECTS		= $(SRCS:.c=.o)

OBJECTSM	= $(MAIN:.c=.o)

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror

# Rules
all: $(NAME)

$(NAME): $(OBJECTS)
	ar rcs $(NAME) $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJECTS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
