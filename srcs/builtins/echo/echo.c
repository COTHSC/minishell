#include "../builtins.h"

int	print_multiple_arguments(char **args, int start, int end)
{
	int	i;

	i = start;
	while(i < end)
	{
		ft_putstr_fd(args[i], 1);
		if (i != end - 1)
			ft_putchar_fd(' ', 1);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	is_only_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != c)
			return (0);
		i++;
	}
	return (1);
}

int	valid_n_option(char *option)
{
	if (ft_strnstr(option, "-n", max_strlen(option, "-n")) - option == 0)
	{
		if (is_only_char((option + 1), 'n'))
			return (1);
		else
			return (0);
	}
	else
		return (0);
}

int ft_echo(int argc, char **argv)
{
	if (argc == 1)
	{
		ft_putchar_fd('\n', 1);
		return (EXIT_SUCCESS);
	}
	else if (argc != 1 && valid_n_option(argv[1]))
	{
		print_multiple_arguments(argv, 2, strlen_list(argv));
		return (EXIT_SUCCESS);
	}
	else
	{
		print_multiple_arguments(argv, 1, strlen_list(argv));
		ft_putchar_fd('\n', 1);
		return (EXIT_SUCCESS);
	}
}
