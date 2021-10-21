/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:05:40 by jescully          #+#    #+#             */
/*   Updated: 2021/10/21 17:03:14 by jescully         ###   ########.fr       */
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
#include "../../libs/libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>

char    **ft_better_split(char const *s);
void    execute(char **command_block, char **env);
char *find_dollars(char *s);
char *remove_quotes(char *s);
int main(int argc, char **argv, char **env)
{
    int i;
    int pid1;
    char **str_tab;
    char buf[PATH_MAX];
    char *line_from_terminal;
    char *prompt;
    char *temp;

    i = argc;
    printf("%s started, fasten your seabelts\n", argv[0]);

    while (1)
    {
        i = 0;

        getcwd(buf, sizeof(buf));
        prompt = ft_strjoin(buf, "$ ");
        line_from_terminal = readline(prompt);
        add_history(line_from_terminal);
        line_from_terminal = find_dollars(line_from_terminal);
        str_tab = ft_better_split(line_from_terminal);
        while (str_tab[i])
        {
            temp =  remove_quotes(str_tab[i]);
            str_tab[i] = temp;
            i++;
        }


        pid1 = fork();

        if (pid1 == 0)
        {
            execute(str_tab, env);
        }
        wait(NULL);

        free(line_from_terminal);
    }

    return 0;
}
