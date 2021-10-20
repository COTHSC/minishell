#include "./libftp.h"

static void	dup_unique_to_str_list(char **dest, char **src, int dest_pos)
{
	int	i;

	i = 0;
	while (!dest[dest_pos])
	{
		if (is_not_in_str_list(dest, src[i]))
		{
			dest[dest_pos] = ft_strdup(src[i]);
			i = 0;
		}
		i++;
	}
}

char	**sort_str_list(char **list)
{
	char	**t;
	int		i;
	int		j;

	j = 0;
	t = calloc_str_list(strlen_list(list));
	while (t && j < strlen_list(list))
	{
		i = 0;
		while (list[i])
		{
			dup_unique_to_str_list(t, list, j);
			if (t[j]
				&& ft_strncmp(t[j], list[i], max_strlen(t[j], list[i])) > 0
				&& is_not_in_str_list(t, list[i]))
			{
				free(t[j]);
				t[j] = ft_strdup(list[i]);
			}
			i++;
		}
		j++;
	}
	return (t);
}
