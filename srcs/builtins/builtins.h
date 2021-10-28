#ifndef BUILTINS_H
# define BUILTINS_H
#include "../../libs/libft/libft.h"
#include "../../libs/libft+/libftp.h"
#include "../../includes/minishell.h"
# include <errno.h>
# include <dirent.h>
# include <limits.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <unistd.h>

/*
** ------------------ BUILTINS FUNCTIONS ------------------
*/
int ft_echo(int argc, char **argv, char ***env);
int ft_cd(int argc, char **argv, char ***env);
int ft_pwd(int argc, char **argv, char ***env);
int ft_export(int argc, char **argv, char ***env);
int	ft_unset(int argc, char **argv, char ***env);
int	ft_env(int argc, char **argv, char ***env);
int ft_exit(int argc, char **argv, char ***env);
/*
** ------------------ BUILTINS AUXILIARIES ------------------
*/
int	var_is_matching(char *var_to_compare, char *var_to_match);
int	count_match_in_var_list(char **var_list, char *var_to_match);
#endif
