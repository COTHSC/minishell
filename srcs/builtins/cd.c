#include "builtins.h"

int ft_cd(int argc, char **argv)
{
    const char *req_path;
    DIR *dir_pointer;

    req_path = argv[1];
    if (argc == 1)
	{
        req_path = ft_getenv("HOME", 'x');
		if (!req_path)
		{
            ft_putstr_fd("minishell: cd: HOME not set\n", 1);
			return (EXIT_FAILURE);
		}
	}
    if (argc > 1 && is_option(argv[1]))
    {
        perror_invalid_option("cd", argv[1], "");
        print_usage_cd();
        return (2);
    }
    if (argc > 2)
    {
        perror_too_many_args("cd");
        return (1);
    }
    dir_pointer = opendir(req_path);
    if(!dir_pointer)
    {
        print_minishell_error(errno, "cd", (char *)req_path);
        return (EXIT_FAILURE);
    }
    else
    {
        closedir(dir_pointer);
        if(chdir(req_path)== -1)
        {
            print_minishell_error(errno,"cd", (char *)req_path);
            return (EXIT_FAILURE);
        }
    }
    return (0);
}
