NAME = libft+.a
LFT= ../libft/libft.a

UNAME_S := $(shell uname -s)
   ifeq ($(UNAME_S),Linux)
        CC=clang
    endif
    ifeq ($(UNAME_S),Darwin)
        CC= clang
    endif

CFLAGS = -Wall -Wextra -Werror 
DFLAGS = -Wall -Wextra -Werror -g
FFLAGS = -fsanitize=address

SRC = ft_iswhitespace.c \
	  ft_isanywordchar.c \
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
	  ft_strtoll.c \
	  ft_test_through_str.c \
	  free_list_and_return_null.c

OBJ  = $(SRC:.c=.o)

all: $(NAME)

debug_lldb : 
	$(MAKE) -C ../libft/ debug_lldb
	$(CC) $(DFLAGS) -c $(SRC)
	ar rc  $(NAME) $? $(OBJ)
	ranlib $(NAME)

debug : 
	$(MAKE) -C ../libft/ debug
	cp ../libft/libft.a ./$(NAME)
	$(CC) $(DFLAGS) $(FFLAGS) -c $(SRC)
	ar rc  $(NAME) $? $(OBJ)
	ranlib $(NAME)

$(NAME): $(OBJ)
	make -C ../libft
	cp ../libft/libft.a ./$(NAME)
	ar rc $(NAME) $? $(OBJ)
	ranlib $(NAME)

so: $(OBJ)
	$(CC) -shared -o libft.so $(OBJ)

clean:
	$(MAKE) -C ../libft/ clean
	/bin/rm -f $(OBJ) $(OBJBON)

fclean: clean
	$(MAKE) -C ../libft/ fclean
	/bin/rm -f $(NAME)

re: fclean all
