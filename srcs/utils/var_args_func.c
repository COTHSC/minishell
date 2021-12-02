#include "../../includes/minishell.h"

void	init_to_zero(int num, ...)
{
	va_list	arguments;
	int		x;

	x = 0;
	va_start(arguments, num);
	while (x++ < num)
		*(va_arg(arguments, int *)) = 0;
	va_end(arguments);
}

void	*free_strs_return_null(int num, ...)
{
	va_list	arguments;
	int		x;

	x = 0;
	va_start(arguments, num);
	while (x++ < num)
		free((va_arg(arguments, char *)));
	va_end(arguments);
	return (0);
}

void	*free_strs_lists(int num, ...)
{
	va_list	arguments;
	int		x;
	char	**temp;

	x = 0;
	va_start(arguments, num);
	while (x++ < num)
	{
		temp = (va_arg(arguments, char **));
		free_str_list(temp, strlen_list(temp));
	}
	va_end(arguments);
	return (0);
}
