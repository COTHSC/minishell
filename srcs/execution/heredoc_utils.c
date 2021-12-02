/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 17:03:07 by jescully          #+#    #+#             */
/*   Updated: 2021/12/02 17:03:08 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_eof_sig(char *del, char buffer[PIPE_BUF], int fds[2], int size)
{
	write(fds[1], buffer, size);
	ft_putstr_fd("minishell: warning: here-doc delimited by eof (wanted, dead \
or alive : ", STDOUT_FILENO);
	ft_putstr_fd(del, STDOUT_FILENO);
	ft_putstr_fd(")", STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	exit(0);
}

int	end_is_heredoc(char *s)
{
	int	str_len;

	str_len = ft_strlen(s);
	if (!s)
		return (0);
	else if (str_len < 2)
		return (0);
	else if (s[str_len - 1] == '<' && s[str_len - 2] == '<')
		return (1);
	else
		return (0);
}

char	*replace_del(char *s, char *delimiter, int fd)
{
	char	*fd_str;
	char	*temp;
	char	*news;

	fd_str = ft_itoa(fd);
	temp = ft_strdup(&s[ft_strlen(delimiter)]);
	news = ft_strjoin(fd_str, temp);
	free(temp);
	free(s);
	s = news;
	free(fd_str);
	return (s);
}

char	*ft_strndup(const char *s, int n)
{
	int		i;
	char	*str;

	i = 0;
	str = (char *)malloc(sizeof(char) * n + 1);
	if (str == NULL)
		return (NULL);
	while (s[i] && i < n)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*get_sep(char *sep_str)
{
	char	**seps;
	char	*sep;

	seps = ft_split(sep_str, '<');
	sep = ft_strdup(seps[0]);
	free_str_list(seps, strlen_list(seps));
	return (sep);
}
