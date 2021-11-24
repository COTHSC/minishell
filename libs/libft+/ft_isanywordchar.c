#include "./libftp.h"

int ft_isanywordchar(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	else
		return (0);
}
