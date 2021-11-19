#ifndef MINISHELL_H
#define MINISHELL_H
# include "../libs/libft+/libftp.h"
# include "../srcs/builtins/builtins.h"
# include "../libs/libft/libft.h"
# include "../get_next_line/get_next_line.h"
# include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
# include <stdlib.h>
# include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

extern char **g_env;

/* Functions used to expand environmental variables */

char *find_dollars(char *s, int status);

/* Functions used to treat and remove quotes from arguments */

char *remove_quotes(char *s);

/* Functions used to split arguments into an an array of strings to be executed */

char    **ft_better_split(char const *s);


/* Functions related to the execution of a child program */

int    execute(char ***command_block);
char    **ft_redirect(char **command_block, int quiet);

//char **env2;
/* OUR builtins */

int select_builtin(int index, int argc, char **argv);

char    *ft_getenv(char *name, char c);
char    *get_path(char **command_block);
void    free_command_block(char **command_block);

/*
** ------------------ BUILTINS AUXILIARIES ------------------
*/
int		select_builtin(int index, int argc, char **argv);
int		builtin_finder(char *name);
int		is_option(char *cmd_block);
int		option_is_called(char *cmd_block, char *option);
int		option_is_called_and_repeated(char *cmd_block, char *option);
void	perror_invalid_option(char *builtin, char *options, char *valid_options);
void	perror_not_a_valid_identifier(char *identifier, char *builtin);
void	perror_numeric_arg_required(char *failing_arg, char *builtin);
void	perror_too_many_args(char *builtin);
void	print_usage_export(void);
void	print_usage_unset(void);
void	print_usage_env(void);
/*
** ------------------ ENV AUXILIARIES ------------------
*/
int		init_env();
char	**ft_exported_vars(char select);
int		var_name_is_matching(char *var_to_compare, char *var_to_match);
char	**match_var_name(char **var_list, char *var_to_match);
char	*extract_value(char *var);
int		var_has_value(char *var);
int		var_is_exported(char *var);
int		var_already_exist(char **var_list, char *var);
void	change_flag(char **var, char flag);
char	**split_to_name_value_pair(char *var);
char	**env_selector(int position_selector);
int		index_matching_var_name(char **var_list, char *var_to_match);
int	alter_env_var(char **clean_env, char *name, char *var_to_add, char *flag);
int	has_valid_identifier(char *var_name);
#endif
