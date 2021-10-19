/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 18:17:44 by jescully          #+#    #+#             */
/*   Updated: 2021/10/19 19:10:34 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <dirent.h>
#include <stdio.h> 
#include <stdio.h>
 #include <stdlib.h>
 #include <errno.h>
 #include "../../../libs/libft/libft.h" 
#include <limits.h>

int main(int argc, char **argv, char **env)
{
    const char *req_path;
    DIR *dir_pointer;
    //char buf[PATH_MAX];

    req_path = argv[1];
    if(!(dir_pointer = opendir(req_path)))
    {
        ft_putstr_fd("minishell: cd: ", 1);
        ft_putstr_fd((char*)req_path, 1);
        ft_putstr_fd(": ", 1);
        perror(NULL);
        return (EXIT_FAILURE);
    }
    else
    {
        closedir(dir_pointer);
    //    getcwd(buf, sizeof(buf));
    //    printf("this is pwd %s\n", buf);
        if(chdir(req_path)== -1)
        {
            ft_putstr_fd("minishell: cd: ", 1);
            ft_putstr_fd((char*)req_path, 1);
            ft_putstr_fd(": ", 1);
            perror(NULL);
            return (EXIT_FAILURE);
        }
    //    getcwd(buf, sizeof(buf));
    //    printf("this is pwd %s\n", buf);
    }
    return (0);
}
