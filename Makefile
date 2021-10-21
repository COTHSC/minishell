NAME = minishell 

SRCS = ./srcs/parsing/ft_better_split.c  \
	   ./srcs/parsing/expand_vars.c  \
	   ./srcs/parsing/main.c  \
	   ./srcs/parsing/remove_quotes.c  \
	   ./srcs/execution/execute.c  \

OBJS = $(SRCS:.c=.o)

UNAME_S := $(shell uname -s)
   ifeq ($(UNAME_S),Linux)
        CC=clang-9
    endif
    ifeq ($(UNAME_S),Darwin)
        CC= clang
    endif

CFLAGS = -Wall -Wextra -Werror

GFLAG = -g3 -fsanitize=address

INCLUDES= -I includes/

all : $(NAME)

$(NAME) : $(OBJS)
	$(MAKE) -C ./libs/libft/
	$(MAKE) -C ./libs/libft+/
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) ./libs/libft/libft.a ./libs/libft+/libft+.a -lreadline

%.o: %.c
	$(CC) -o $@ -c $^ $(CFLAGS) $(INCLUDES)

debug :
	$(MAKE) -C ./libs/libft/
	$(MAKE) -C ./libs/libft+/
	$(CC) $(CFLAGS) $(GFLAG) -o $(NAME) $(SRCS) ./libs/libft/libft.a ./libs/libft+/libft+.a -lreadline

debug_unsanitary :
	$(MAKE) -C ./libs/libft/
	$(MAKE) -C ./libs/libft+/
	$(CC) $(CFLAGS) -g -o $(NAME) $(SRCS) ./libs/libft/libft.a ./libs/libft+/libft+.a -lreadline

clean :
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)

re: fclean all
