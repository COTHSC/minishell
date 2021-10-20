/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:05:40 by jescully          #+#    #+#             */
/*   Updated: 2021/10/20 15:10:33 by jescully         ###   ########.fr       */
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


char *find_dollars(char *s);
char    **ft_better_split(char const *s);


int main(int argc, char **argv)
{
    int i;
    char **str_tab;

    i = 0;
    while (str_tab[i])
    {
        printf("str[%d] : %s\n", i, str_tab[i]);
        i++;
    }
    printf("str[%d] : %s\n", i, str_tab[i]);
    return 0;
}
