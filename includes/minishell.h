/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:46:59 by calle             #+#    #+#             */
/*   Updated: 2021/10/28 16:27:44 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libs/libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include "../libs/libft+/libftp.h"
# include "../srcs/builtins/builtins.h"
# include <stdio.h>


/* Functions used to expand environmental variables */

char *find_dollars(char *s, int status);

/* Functions used to treat and remove quotes from arguments */

char *remove_quotes(char *s);

/* Functions used to split arguments into an an array of strings to be executed */

char    **ft_better_split(char const *s);


/* Functions related to the execution of a child program */

int    execute(char **command_block, char ***env);

//char **env2;
/* OUR builtins */

int select_builtin(int index, int argc, char **argv, char ***env);
int ft_pwd(int argc, char **argv, char ***env);

char    *getenv2(char **env, char *name);
char    *get_path(char **command_block);
int builtin_finder(char *name);
void    free_command_block(char **command_block);
int init_env(char **env2);
char **ft_exported_vars(char **env, char select);
#endif
