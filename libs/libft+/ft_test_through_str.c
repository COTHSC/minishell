#include "./libftp.h"

int ft_test_through_str(char *str_to_check, int (*test)(int))
{
    int i;

    if (!str_to_check)
        return (-1);
    i = 0;
    while (str_to_check[i])
    {
        if (test(str_to_check[i]) == 0)
            return (0);
        i++;
    }
    return (1);
}

