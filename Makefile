NAME = minishell 

SRCS = ./srcs/parsing/ft_better_split.c  \
	   ./srcs/main/main.c  \
	   ./srcs/main/parse_commandline.c  \
	   ./srcs/parsing/expand_vars.c  \
	   ./srcs/parsing/ft_pipe_split.c  \
	   ./srcs/parsing/remove_quotes.c  \
	   ./srcs/parsing/syntax_handlers.c  \
	   ./srcs/parsing/parse_syntax.c  \
	   ./srcs/parsing/expand_utils.c  \
	   ./srcs/parsing/parse_declarations.c  \
	   ./srcs/execution/execute.c  \
	   ./srcs/execution/redirect.c  \
	   ./srcs/execution/pathfinders.c  \
	   ./srcs/execution/make_heredocs.c  \
	   ./srcs/execution/init_minishell.c  \
	   ./srcs/execution/pipe_utils.c  \
	   ./srcs/execution/redirect_utils.c  \
	   ./srcs/execution/execute_pipes.c  \
	   ./srcs/execution/get_commands.c  \
	   ./srcs/execution/execute_single_cmd.c  \
	   ./srcs/execution/heredoc_utils.c  \
	   ./srcs/execution/heredoc_parsing.c  \
	   ./srcs/execution/execution_utils.c  \
	   ./srcs/execution/execution_utils2.c  \
	   ./srcs/execution/signal_handling.c  \
	   ./srcs/execution/term_settings.c  \
	   ./srcs/execution/term_reset.c  \
	   ./srcs/execution/term_setchers.c  \
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
	   ./srcs/utils/var_args_func.c \
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
	@echo "make: compiling sources and libs..."
	@$(MAKE) --quiet -C ./libs/libft+/
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) ./libs/libft+/libft+.a -lreadline
	@echo "✔ Done"

%.o: %.c
	@$(CC) -o $@ -c $^ $(CFLAGS) $(INCLUDES)

debug :
	@echo "make: compiling sources and libs with fsanitize flag..."
	@$(MAKE) --quiet -C ./libs/libft+/ debug
	@$(CC) $(CFLAGS) $(GFLAG) -o $(NAME) $(SRCS) ./libs/libft+/libft+.a -lreadline
	@echo "✔ Done"

debug_lldb :
	@echo "make: compiling sources and libs with debug flag..."
	@$(MAKE) --quiet -C ./libs/libft+/ debug_lldb
	@$(CC) $(CFLAGS) -g -o $(NAME) $(SRCS) ./libs/libft+/libft+.a -lreadline
	@echo "✔ Done"

clean :
	@echo "make: cleaning object files..."
	@rm -f $(OBJS)
	@$(MAKE) --quiet -C ./libs/libft+/ clean
	@echo "✔ Done"

fclean:	clean
	@echo "make: cleaning executable..."
	rm -f $(NAME)
	@$(MAKE) --quiet -C ./libs/libft+/ fclean
	@echo "✔ Done"

re: fclean all

.PHONY: all debug debug_lldb clean fclean re
