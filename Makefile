# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/08 11:20:21 by jqueijo-          #+#    #+#              #
#    Updated: 2024/01/23 14:42:16 by jqueijo-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRC = pipex.c \
		pipex_utils.c \
		aux_functions.c \
		ft_split.c \

CC = cc

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	cc -o pipex $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

real: CFLAGS += -Wall -Werror -Wextra

real: all

re: fclean all

.PHONY: all, bonus, clean, fclean, re
