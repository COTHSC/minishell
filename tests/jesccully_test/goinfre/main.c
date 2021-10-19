/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:05:40 by jescully          #+#    #+#             */
/*   Updated: 2021/10/19 10:54:43 by jescully         ###   ########.fr       */
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
#include "./libft/libft.h"


int main(int argc, char **argv)
{
    char buf[PATH_MAX];
    char *line_from_terminal;
    char *prompt;

    while (1)
    {
        getcwd(buf, sizeof(buf));
        prompt = ft_strjoin(buf, "$ ");
        line_from_terminal = readline(prompt);
        
        if (ft_strncmp(line_from_terminal, "cd", 3))
            chdir("/Users/jescully/Documents");

        add_history(line_from_terminal);
        free(line_from_terminal);
    }

    clear_history();

    return 0;
}
