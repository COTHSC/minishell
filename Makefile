NAME = minishell 

SRCS = ./srcs/parsing/ft_better_split.c  \
	   ./srcs/main/main.c  \
	   ./srcs/parsing/expand_vars.c  \
	   ./srcs/parsing/ft_pipe_split.c  \
	   ./srcs/parsing/remove_quotes.c  \
	   ./srcs/parsing/parse_syntax.c  \
	   ./srcs/parsing/parse_declarations.c  \
	   ./srcs/execution/execute.c  \
	   ./srcs/execution/redirect.c  \
	   ./srcs/execution/pathfinders.c  \
	   ./srcs/execution/make_heredocs.c  \
	   ./srcs/execution/init_minishell.c  \
	   ./srcs/execution/signal_handling.c  \
	   ./srcs/execution/term_settings.c  \
	   ./srcs/execution/term_reset.c  \
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
	   ./srcs/env_handling/check_and_alter_env.c \
	   ./get_next_line/get_next_line.c \
	   ./get_next_line/get_next_line_utils.c \
	   ./srcs/utils/print_builtins_usage.c \
	   ./srcs/utils/print_builtins_errors.c \
	   ./srcs/utils/print_minishell_errors.c

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
	$(MAKE) -C ./libs/libft+/
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) ./libs/libft+/libft+.a -lreadline

%.o: %.c
	$(CC) -o $@ -c $^ $(CFLAGS) $(INCLUDES)

debug :
	$(MAKE) -C ./libs/libft+/ debug
	$(CC) $(CFLAGS) $(GFLAG) -o $(NAME) $(SRCS) ./libs/libft+/libft+.a -lreadline

debug_lldb :
	$(MAKE) -C ./libs/libft+/ debug_lldb
	$(CC) $(CFLAGS) -g -o $(NAME) $(SRCS) ./libs/libft+/libft+.a -lreadline

clean :
	rm -f $(OBJS)
	$(MAKE) -C ./libs/libft+/ clean

fclean:	clean
	rm -f $(NAME)
	$(MAKE) -C ./libs/libft+/ fclean

re: fclean all
