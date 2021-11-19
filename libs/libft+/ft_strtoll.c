#include "./libftp.h"

static int	out_of_ll_range(unsigned long long num, int sign)
{
	unsigned long long	min_abs;
	

	min_abs = (unsigned long long)(-1 * (LLONG_MIN + 1)) + 1;
	if (sign < 0)
	{
		if (num > min_abs)
			return (1);
		else
			return (0);
	}
	else
	{
		if ((unsigned long long)LLONG_MAX < num)
			return (1);
		else
			return (0);
	}
}

long long	ft_strtoll(char *str, int *out_of_range)
{
	int			i;
	int			sign;
	unsigned long long	num;

	i = 0;
	sign = 1;
	num = 0;
	*out_of_range = 0;
	while (ft_iswhitespace(str[i]))
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]) && !(*out_of_range))
	{
		num = num * 10 + (str[i] - '0');
		*out_of_range = out_of_ll_range(num, sign);
		i++;
	}
	return (sign * num);
}
