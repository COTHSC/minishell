# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jescully <jescully@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/18 09:50:54 by jescully          #+#    #+#              #
#    Updated: 2021/10/28 15:13:10 by jescully         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft+.a

CC = clang

CFLAGS = -Wall -Wextra -Werror 
DFLAGS = -Wall -Wextra -Werror -g
FFLAGS = -fsanitize=address

SRC = ft_iswhitespace.c \
	  max_strlen.c \
	  free_str_list.c \
	  calloc_str_list.c \
	  is_not_in_str_list.c \
	  print_str_list.c \
	  sort_str_list.c \
	  strlen_list.c \
	  str_add.c \
	  str_list_join.c \
	  str_list_dup.c \
	  free_list_and_return_null.c

OBJ  = $(SRC:.c=.o)

all: $(NAME)

debug_lldb : 
	$(CC) $(DFLAGS) -c $(SRC)
	ar rc  $(NAME) $? $(OBJ)
	ranlib $(NAME)

debug : 
	$(CC) $(DFLAGS) $(FFLAGS) -c $(SRC)
	ar rc  $(NAME) $? $(OBJ)
	ranlib $(NAME)

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

