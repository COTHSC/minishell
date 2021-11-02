#ifndef BUILTINS_H
# define BUILTINS_H
#include "../../../libs/libft/libft.h"
#include "../../../libs/libft+/libftp.h"
# include <errno.h>
# include <dirent.h>
# include <limits.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <unistd.h>

int ft_echo(int argc, char **argv, char **env);
int ft_cd(int argc, char **argv, char **env);
int ft_pwd(int argc, char **argv, char **env);
int ft_export(int argc, char **argv, char **env);
int	ft_unset(int argc, char **argv, char ***env);
int	ft_env(int argc, char **argv, char **env);
int ft_exit(int argc, char **argv, char **env);

#endif
