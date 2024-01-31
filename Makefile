# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/08 11:20:21 by jqueijo-          #+#    #+#              #
#    Updated: 2024/01/31 12:54:40 by jqueijo-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRC = pipex.c \
		pipex_utils.c \
		aux_functions.c \
		ft_split.c \

CC = cc
CFLAGS = -Wall -Werror -Wextra
SANITIZER = -g -fsanitize=address

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

debug: CFLAGS += $(SANITIZER)
debug: re

re: fclean all

.PHONY: all, bonus, clean, fclean, re
