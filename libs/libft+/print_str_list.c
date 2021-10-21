#include "./libftp.h"

void	print_str_list(char **str_list, char *print_before_list)
{
	int	i;

	i = 0;
	while (str_list[i])
	{
		if (print_before_list)
			ft_putstr_fd(print_before_list, 1);
		ft_putstr_fd(str_list[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
}
