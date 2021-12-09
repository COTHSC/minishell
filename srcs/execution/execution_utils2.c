/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:08:08 by jescully          #+#    #+#             */
/*   Updated: 2021/12/09 18:51:27 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	wait_and_return(int fds[2])
{
	int	status;

	status = wait_and_get_status();
	setcher(status);
	close(fds[1]);
	reset_parent_tio_settings();
	signal_handler_settings();
	return (status);
}

void	handle_sig_hd(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	(void)info;
	if (sig == SIGINT)
	{
		write(1, "^C", 2);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		exit(130);
	}
}

void	set_signal_handler_heredoc(void)
{
	static struct sigaction	sa_hd;

	reset_hd_tio_settings();
	signal(SIGINT, SIG_IGN);
	sa_hd.sa_sigaction = &handle_sig_hd;
	sa_hd.sa_flags = SA_RESTART | SA_SIGINFO;
	sigaction(SIGINT, &sa_hd, NULL);
}

void	remove_quotes_list(char **command_block)
{
	int		i;
	char	*temp;

	i = 0;
	while (command_block[i])
	{
		temp = remove_quotes(command_block[i]);
		command_block[i] = temp;
		i++;
	}
}
