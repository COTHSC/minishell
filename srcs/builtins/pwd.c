#include "builtins.h"

int ft_pwd(int argc, char **argv)
{
    char buf[PATH_MAX];
    char *current_workdir;
    if (argc > 1 && is_option(argv[1]))
    {
        perror_invalid_option("pwd", argv[1], "");
        return (2);
    }
    current_workdir = getcwd(buf, sizeof(buf));
    if (!current_workdir)
    {
        //print_minishell_error(errno, )
        return (EXIT_FAILURE);
    }
    else
    {
        ft_putstr_fd(buf, 1);
        ft_putstr_fd("\n", 1);
        return (0);
    }
}
