/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_setchers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 16:11:06 by calle             #+#    #+#             */
/*   Updated: 2021/12/02 16:11:08 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

struct	termios	*setch_hd_tio(int switch_off)
{
	static struct termios	hd_tio;
	int						ret;

	if (!switch_off)
	{
		if (!isatty(STDIN_FILENO))
		{
			return (NULL);
		}
		ret = tcgetattr(STDIN_FILENO, &hd_tio);
		if (ret < 0)
		{
			perror ("error in tcgetattr");
			return (NULL);
		}
	}
	return (&hd_tio);
}

struct termios	*setch_og_tio(int switch_off)
{
	static struct termios	og_tio;
	int						ret;

	if (!switch_off)
	{
		if (!isatty(STDIN_FILENO))
		{
			return (NULL);
		}
		ret = tcgetattr(STDIN_FILENO, &og_tio);
		if (ret < 0)
		{
			perror ("error in tcgetattr");
			return (NULL);
		}
	}
	return (&og_tio);
}

struct termios	*setch_parent_tio(int switch_off)
{
	static struct termios	parent_tio;
	int						ret;

	if (!switch_off)
	{
		if (!isatty(STDIN_FILENO))
		{
			return (NULL);
		}
		ret = tcgetattr(STDIN_FILENO, &parent_tio);
		if (ret < 0)
		{
			perror ("error in tcgetattr");
			return (NULL);
		}
	}
	return (&parent_tio);
}
