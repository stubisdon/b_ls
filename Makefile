# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dkotov <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/17 15:19:18 by dkotov            #+#    #+#              #
#    Updated: 2018/09/21 13:12:27 by dkotov           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRC = main.c \
		lists.c \
		sort.c \
		ft_strjoin.c 

OBJ = main.o

HEAD = ft_ls.h

FLAGS = -Wall -Werror -Wextra

DEBUGMEM = -fsanitize=address

all: $(NAME)

$(NAME):
	gcc $(FLAGS) -g -o $(NAME) $(SRC) $(DEBUGMEM)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean
	make all
