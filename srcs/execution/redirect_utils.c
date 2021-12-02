#include "../../includes/minishell.h"

int	is_redirect(char c)
{
	if (c == '>')
		return (1);
	else if (c == '<')
		return (3);
	return (0);
}

int	is_path(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

char	**delete_str(char **str_list, int index)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	j = 0;
	tmp = calloc_str_list(strlen_list(str_list));
	if (!tmp)
		return (NULL);
	while (str_list[i])
	{
		if (i == index)
			j--;
		else
		{
			tmp[j] = ft_strdup(str_list[i]);
			if (!tmp[j])
				return (free_list_and_return_null(tmp, j));
		}
		j++;
		i++;
	}
	free_str_list(str_list, strlen_list(str_list));
	return (tmp);
}

int	exec_dup(int redirect_type, int fd)
{
	if (redirect_type < 3)
		dup2(fd, STDOUT_FILENO);
	else
		dup2(fd, STDIN_FILENO);
	return (0);
}

int	get_redirect_and_skip(char *s, int *i)
{
	int	redirect_type;

	redirect_type = 0;
	while (s[*i] && is_redirect(s[*i]))
	{
		redirect_type += is_redirect(s[*i]);
		*i += 1;
	}
	return (redirect_type);
}
