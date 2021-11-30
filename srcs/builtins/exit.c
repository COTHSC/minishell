#include "builtins.h"

int is_valid_status(char *arg)
{
	int	i;
	char	sign;	

	i = 0;
	sign = 0;
	if (*arg == 0)
		return (0);
	while (arg[i])
	{
		if (arg[i] == '-' || arg[i] == '+')
		{
			if (sign != 0)
				return (0);
			else
				sign = arg[i];
		}
		else if (!ft_isdigit(arg[i]) && !ft_iswhitespace(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

int ft_exit(int argc, char **argv)
{
	unsigned char	exit_status;
	int		out_of_range;

	out_of_range = 0;
	if (argc == 1)	
	{
		//No arg supplied return previous exit status
		ft_putstr_fd("exit \n", STDERR_FILENO);
		return (-1);
	}
	else if (!is_valid_status(argv[1]))
	{
		ft_putstr_fd("exit \n", STDERR_FILENO);
		perror_numeric_arg_required(argv[1], "exit");
		return (2);
	}
	else if (argc > 2)
	{
		//In case of multiple args, exit do not exit and return a status of 1
		ft_putstr_fd("exit \n", STDERR_FILENO);
		perror_too_many_args("exit");
		return (1);
	}
	else
	{
		exit_status = (unsigned char)ft_strtoll(argv[1], &out_of_range);
		ft_putstr_fd("exit \n", STDERR_FILENO);
		if (out_of_range == 1)
		{
			//If the exit status passed is out of long long range
			perror_numeric_arg_required(argv[1], "exit");
			return (2);
		}
		return (exit_status);
	}
}
