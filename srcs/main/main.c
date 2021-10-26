/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:05:40 by jescully          #+#    #+#             */
/*   Updated: 2021/10/26 19:15:32 by jescully         ###   ########.fr       */
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


int main(int argc, char **argv, char **env)
{
    int i;
    char **str_tab;
    char buf[PATH_MAX];
    char *line_from_terminal;
    char *prompt;
    char *temp;
    int es;
    char **env2;

    env2 = str_list_dup(env);
    printf("%s started, fasten your seabelts\n", argv[0]);
    es = 0;
    (void)argc;
    while (1)
    {
        i = 0;
        getcwd(buf, sizeof(buf));
        prompt = ft_strjoin(buf, "$ ");
        line_from_terminal = readline(prompt);
        add_history(line_from_terminal);
        line_from_terminal = find_dollars(line_from_terminal, es);
        str_tab = ft_better_split(line_from_terminal);
        while (str_tab[i])
        {
            temp =  remove_quotes(str_tab[i]);
            str_tab[i] = temp;
            i++;
        }
        es = execute(str_tab, env2);
        free(line_from_terminal);
    }
    return 0;
}
