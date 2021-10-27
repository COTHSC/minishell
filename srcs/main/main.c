/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:05:40 by jescully          #+#    #+#             */
/*   Updated: 2021/10/27 13:29:18 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <limits.h>
#include "../../includes/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

void    remove_quotes_list(char **str_list)
{
    int i;
    char *temp;

    i = 0;
    while (str_list[i])
    {
        temp =  remove_quotes(str_list[i]);
        str_list[i] = temp;
        i++;
    }

}

void    readline_loop(char **env)
{
    char **str_tab;
    char *line_from_terminal;
    int es;

    es = 0;
    while (1)
    {
        line_from_terminal = readline("minishell >  ");
        add_history(line_from_terminal);
        line_from_terminal = find_dollars(line_from_terminal, es);
        str_tab = ft_better_split(line_from_terminal);
        remove_quotes_list(str_tab);
        es = execute(str_tab, &env);
        free(line_from_terminal);
    }
}

int main(int argc, char **argv, char **env)
{
    char **env2;

    (void)argc;
    (void)argv;
    env2 = str_list_dup(env);
    readline_loop(env2);
    return 0;
}
