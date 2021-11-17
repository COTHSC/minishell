#include "builtins.h"

int ft_cd(int argc, char **argv)
{
    const char *req_path;
    DIR *dir_pointer;

    req_path = argv[1];
    if (argc == 1)
	{
        req_path = ft_getenv("HOME");
		if (!req_path)
		{
			//"HOME not set" should be return;
			return (EXIT_FAILURE);
		}
	}
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
