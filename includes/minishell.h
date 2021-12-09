/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 20:58:04 by jescully          #+#    #+#             */
/*   Updated: 2021/12/09 21:20:26 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 minishell.h										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: jescully <marvin@42.fr>					+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2021/12/09 20:45:59 by jescully		   #+#	  #+#			  */
/*	 Updated: 2021/12/09 20:48:19 by jescully		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libs/libft+/libftp.h"
# include "../srcs/builtins/builtins.h"
# include "../libs/libft/libft.h"
# include "../get_next_line/get_next_line.h"
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <termios.h>
# include <signal.h>

extern char	**g_env;

typedef struct s_redir {
	int		es;
	char	**cmd;
	int		fd[FD_SETSIZE];
}	t_redir;
/*
 ** ------------------ PARSING MODULES ------------------
 */
int				parse_command_line(char *line_from_terminal, int *es);
char			**parse_declaration(char **command_blocks);
int				setcher(int newvalue);
void			pick_a_prompt(char **line_from_terminal);
int				is_done(char *s);
void			print_cmd_error(char *cmd);
char			*ft_strndup(const char *s, int n);
char			*get_heredoc(char *s, int i);
char			*parse_line(char *s);
char			**parse_block(char **cmd_block);
char			**delete_str(char **str_list, int index);
int				get_redirect_and_skip(char *s, int *i);
int				select_builtin_test(int index, int argc, char **argv);
void			free_command_block(char **command_block);
int				execute_binary(char **command_block);
int				nb_cmds(char ***cmd);
int				check_if_file(char **cmd);
int				handle_semicolons(char *s, int i);
int				handle_redirects(char *s, int i);
int				handle_pipes(char *s, int i);
int				handle_quotes(char *s, int *i);
void			print_file_error(int error, char *filename);
int				get_redirect_type(char *s);
int				check_quotes(char *s);
int				check_between_the_pipes(char *s);
int				check_between_the_redirects(char *s);
char			*remove_quote(char *str, int i);
char			**ft_pipe_split(char const *s);
char			**parse_block(char **command_block);
int				check_fd(int fd, char *filename);
int				is_path(char *s);
int				basic_checks(char *line_from_terminal, int *es);
char			***prepare_command_list(char **commands);
int				handle_synthax_error(char *line_from_terminal);
/*
 ** ------------------ EXPANSION ------------------
 */
int				check_syntax(char *s);
int				isquote(char c);
char			*get_var_name(char *s, int *i);
char			*get_var_value(char *var_name, int *offset, int status);
int				deal_with_quotes(char *s, int *quote, int *i);
char			*find_dollars(char *s, int status);
int				go_through_quote(char const *s, int lead, int *quote);
void			perror_syntax_error(char unexpected_token);

/*
 ** ------------------ QUOTES ------------------
 */
char			*remove_quotes(char *s);
void			remove_quotes_list(char **command_block);
char			**get_command(char **cmd_block);
char			**ft_better_split(char const *s);
/*
 ** ------------------ EXECUTION ------------------
 */
int				wait_and_return(int fds[2]);
char			*get_sep(char *sep_str);
void			ft_replug(int stdio_cpy[2]);
int				single_cmd(char **cmd);
int				ft_multipipes2(char ***cmd);
int				wait_and_get_status(void);
int				exec_dup(int redirect_type, int fd);
int				close_unused_fds(int (*fd)[2], int current, int nb_cmds);
int				make_pipes(int (*fd)[2], int size);
char			*make_heredocs(char *seps, int fd[2]);
void			close_fds(int fd[FD_SETSIZE]);
int				execute_child(int (*fd)[2], int i, int n, char **cmd);
int				exec_heredoc(char *separator, int fds[2]);
int				execute(char ***command_block);
char			**ft_redirect(t_redir *redir);
int				is_redirect(char c);
int				end_is_heredoc(char *s);
char			*replace_del(char *s, char *delimiter, int fd);
/*
 ** ------------------ SHELL INIT ------------------
 */
int				init_minishell(char **env);
void			init_split(int *row, int *lead, int *quote);
int				init_env(void);
void			init_fds(int fd[FD_SETSIZE]);
/*
 ** ------------------ BUILTINS AUXILIARIES ------------------
 */	
int				select_builtin(int index, int argc, char **argv);
int				select_builtin(int index, int argc, char **argv);
char			*ft_getenv(char *name, char c);
char			*get_path(char **command_block);
void			free_command_block(char **command_block);
int				builtin_finder(char *name);
int				is_option(char *cmd_block);
int				option_is_called(char *cmd_block, char *option);
int				option_is_called_and_repeated(char *cmd_block, char *option);
void			perror_invalid_option(char *builtin, char *options, \
		char *valid_options);
void			perror_not_a_valid_identifier(char *identifier, char *builtin);
void			perror_numeric_arg_required(char *failing_arg, char *builtin);
void			perror_too_many_args(char *builtin);
void			print_minishell_error(int error, char *cmd, char *path);
void			print_usage_export(void);
void			print_usage_unset(void);
void			print_usage_env(void);
void			print_usage_cd(void);
/*
 ** ------------------ ENV AUXILIARIES ------------------
 */
char			**ft_exported_vars(char select);
int				var_name_is_matching(char *var_to_compare, char *var_to_match);
char			**match_var_name(char **var_list, char *var_to_match);
char			*extract_value(char *var);
int				var_has_value(char *var);
int				var_is_exported(char *var);
int				var_already_exist(char **var_list, char *var);
void			change_flag(char **var, char flag);
char			**split_to_name_value_pair(char *var);
char			**env_selector(int position_selector, char *flag);
int				index_matching_var_name(char **var_list, char *var_to_match);
int				alter_env_var(char **clean_env, char *name, char *var_to_add, \
		char *flag);
int				check_and_alter_env(char **args, char *flag);
int				has_valid_var_name(char *var);
int				find_index_of_char(char *s, char c);
/*
 ** ------------------ TERM AUXILIARIES ------------------
 */
struct termios	*setch_og_tio(int switch_off);
struct termios	*setch_parent_tio(int switch_off);
struct termios	*setch_hd_tio(int switch_off);
int				reset_og_tio_settings(void);
int				reset_parent_tio_settings(void);
int				reset_hd_tio_settings(void);
int				terminal_settings(void);
/*
 ** ------------------ SIGNAL HANDLING ------------------
 */
void			signal_handler_settings(void);
void			handle_eof_sig(char *del, char buffer[PIPE_BUF], int fds[2], \
		int size);
void			handle_sig_hd(int sig, siginfo_t *info, void *ucontext);
void			set_signal_handler_heredoc(void);
#endif
