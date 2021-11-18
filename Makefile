NAME = minishell 

SRCS = ./srcs/parsing/ft_better_split.c  \
	   ./srcs/main/main.c  \
	   ./srcs/parsing/expand_vars.c  \
	   ./srcs/parsing/remove_quotes.c  \
	   ./srcs/execution/execute.c  \
	   ./srcs/execution/redirect.c  \
	   ./srcs/execution/pathfinders.c  \
	   ./srcs/builtins/builtin_selector.c  \
	   ./srcs/builtins/pwd.c  \
	   ./srcs/builtins/cd.c  \
	   ./srcs/builtins/exit.c  \
	   ./srcs/builtins/echo.c  \
	   ./srcs/builtins/export.c  \
	   ./srcs/builtins/env.c  \
	   ./srcs/builtins/unset.c  \
	   ./srcs/utils/our_get_env.c  \
	   ./srcs/utils/init_env.c  \
	   ./srcs/utils/get_exported_vars.c  \
	   ./srcs/utils/env_checkers.c \
	   ./srcs/utils/env_modifiers.c \
	   ./srcs/utils/match_env_var.c \
	   ./srcs/utils/split_var_by_name_value_pair.c \
	   ./srcs/utils/env_selector.c \
	   ./srcs/utils/command_options_checkers.c \
	   ./srcs/utils/print_builtins_usage.c \
	   ./srcs/utils/print_builtins_errors.c

OBJS = $(SRCS:.c=.o)

UNAME_S := $(shell uname -s)
   ifeq ($(UNAME_S),Linux)
        CC=clang
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
	$(MAKE) -C ./libs/libft/ debug
	$(MAKE) -C ./libs/libft+/ debug
	$(CC) $(CFLAGS) $(GFLAG) -o $(NAME) $(SRCS) ./libs/libft/libft.a ./libs/libft+/libft+.a -lreadline

debug_lldb :
	$(MAKE) -C ./libs/libft/ debug_lldb
	$(MAKE) -C ./libs/libft+/ debug_lldb
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
