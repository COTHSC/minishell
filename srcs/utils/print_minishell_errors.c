#include "../../includes/minishell.h"

void    print_minishell_error(int error, char *str)
{
     ft_putstr_fd("minishell: cd: ", 2);
     ft_putstr_fd(str, 2);
     ft_putstr_fd(": ", 2);
     ft_putstr_fd(strerror(error), 2);
     ft_putstr_fd("\n", 2);
}
