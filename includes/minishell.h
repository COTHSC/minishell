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
 # include <fcntl.h>

extern char **g_env;



typedef struct s_redir {
	int es;
	char **cmd;
    int fd[100];
}	t_redir;

char *remove_quote(char *str, int i);
char	**ft_pipe_split(char const *s);
char    **parse_block(char **command_block);
int	execute_child(int (*fd)[2], int i, int n, char **cmd);
int    check_fd(int fd, char *filename);
/* Functions used to expand environmental variables */
int check_syntax(char *s);
int isquote(char c);

int check_redirect_type(int redirect_type);
char *find_dollars(char *s, int status);

int go_through_quote(char const *s, int lead, int *quote);
void	perror_syntax_error(char unexpected_token);
/* Functions used to treat and remove quotes from arguments */

char *remove_quotes(char *s);

void   remove_quotes_list(char **command_block);
char **get_command(char **cmd_block);
/* Functions used to split arguments into an an array of strings to be executed */

char    **ft_better_split(char const *s);


/* Functions related to the execution of a child program */

int    execute(char ***command_block);
char    **ft_redirect(t_redir *redir);
int     is_redirect(char c);

//char **env2;
/* OUR builtins */

int select_builtin(int index, int argc, char **argv);

char    *ft_getenv(char *name, char c);
char    *get_path(char **command_block);
void    free_command_block(char **command_block);
/*
** ------------------ PARSING ------------------
*/
char	**parse_declaration(char **command_blocks);
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
void    print_minishell_error(int error, char *str);
void	print_usage_export(void);
void	print_usage_unset(void);
void	print_usage_env(void);
void	print_usage_cd(void);
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
char	**env_selector(int position_selector, char *flag);
int		index_matching_var_name(char **var_list, char *var_to_match);
int	alter_env_var(char **clean_env, char *name, char *var_to_add, char *flag);
int	check_and_alter_env(char **args, char *flag);
int	has_valid_identifier(char *var_name);
#endif
