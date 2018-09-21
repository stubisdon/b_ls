# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dkotov <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/17 15:19:18 by dkotov            #+#    #+#              #
#    Updated: 2018/09/18 14:53:49 by dkotov           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRC = main.c \
		lists.c

OBJ = main.o

HEAD = ft_ls.h

FLAGS = -Wall -Werror -Wextra

DEBUGMEM = -fsanitize=address

all: $(NAME)

$(NAME):
	gcc $(FLAGS) -g -o $(NAME) $(SRC)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean
	make all
