#include "../builtins.h"

int ft_cd(int argc, char **argv, char ***env)
{
    const char *req_path;
    DIR *dir_pointer;

	(void)env;
    req_path = argv[1];
    if (argc == 1)
        req_path = getenv2(*env, "HOME");
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
        if(chdir(req_path)== -1)
        {
            ft_putstr_fd("minishell: cd: ", 1);
            ft_putstr_fd((char*)req_path, 1);
            ft_putstr_fd(": ", 1);
            perror(NULL);
            return (EXIT_FAILURE);
        }
    }
    return (0);
}
