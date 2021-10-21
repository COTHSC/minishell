# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jescully <jescully@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/18 09:50:54 by jescully          #+#    #+#              #
#    Updated: 2021/10/20 18:43:51 by calle            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftp.a

CC = clang

CFLAGS = -Wall -Wextra -Werror

SRC = ft_iswhitespace.c \
	  max_strlen.c \
	  free_str_list.c \
	  calloc_str_list.c \
	  is_not_in_str_list.c \
	  print_str_list.c \
	  sort_str_list.c \
	  strlen_list.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $? $(OBJ)
	ranlib $(NAME)

so: $(OBJ)
	$(CC) -shared -o libft.so $(OBJ)

clean:
	/bin/rm -f $(OBJ) $(OBJBON)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

