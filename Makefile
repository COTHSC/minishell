NAME = minishell 

SRCS = ./srcs/parsing/ft_better_split.c  \
	   ./srcs/parsing/expand_vars.c  \
	   ./srcs/main/main.c  \
	   ./srcs/parsing/remove_quotes.c  \
	   ./srcs/execution/execute.c  \
	   ./srcs/execution/pathfinders.c  \
	   ./srcs/builtins/builtin_selector_test.c  \
	   ./srcs/builtins/pwd/pwd.c  \
	   ./srcs/builtins/cd/cd.c  \
	   ./srcs/builtins/exit/exit.c  \
	   ./srcs/builtins/export/export.c  \
	   ./srcs/builtins/env/env.c  \
	   ./srcs/builtins/unset/unset.c  \
	   ./srcs/builtins/echo/echo.c  \
	   ./srcs/utils/our_get_env.c  \
	   ./srcs/utils/init_env.c  \

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
	$(MAKE) -C ./libs/libft/ clean
	$(MAKE) -C ./libs/libft+/ clean

fclean:	clean
	rm -f $(NAME)
	$(MAKE) -C ./libs/libft/ fclean
	$(MAKE) -C ./libs/libft+/ fclean

re: fclean all
