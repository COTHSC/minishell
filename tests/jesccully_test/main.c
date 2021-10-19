/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:05:40 by jescully          #+#    #+#             */
/*   Updated: 2021/10/19 13:56:00 by jescully         ###   ########.fr       */
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


 char    **ft_better_split(char const *s, char c);


int main(int argc, char **argv)
{
    int i;
    char **str_tab;

    i = 0;
    str_tab = ft_better_split("one \"with a sentence in it\"andsomethingrightafter \" and another full sentence with            spaces\"  ' and another with single quotes'  \"and now single quotes within double quotes '   ere ' \"  'and finale double quotes within single quotes\"hi hi\" ' sentence", ' ');
    str_tab = ft_better_split("echo -n\"hello world\"             ' and another sentence' ' and one last one' ", ' ');
    while (str_tab[i])
    {
        printf("str[%d] : %s\n", i, str_tab[i]);
        i++;
    }
    printf("str[%d] : %s\n", i, str_tab[i]);
    return 0;
}
