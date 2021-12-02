/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_reset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 16:11:02 by calle             #+#    #+#             */
/*   Updated: 2021/12/02 16:11:04 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	reset_og_tio_settings(void)
{
	int	ret;

	if (!isatty(STDIN_FILENO))
	{
		return (EXIT_SUCCESS);
	}
	ret = tcsetattr(STDIN_FILENO, TCSANOW, setch_og_tio(1));
	if (ret < 0)
	{
		perror ("error in tcsetattr");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	reset_parent_tio_settings(void)
{
	int	ret;

	if (!isatty(STDIN_FILENO))
	{
		return (EXIT_SUCCESS);
	}
	ret = tcsetattr(STDIN_FILENO, TCSANOW, setch_parent_tio(1));
	if (ret < 0)
	{
		perror ("error in tcsetattr");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	reset_hd_tio_settings(void)
{
	int	ret;

	if (!isatty(STDIN_FILENO))
	{
		return (EXIT_SUCCESS);
	}
	ret = tcsetattr(STDIN_FILENO, TCSANOW, setch_hd_tio(1));
	if (ret < 0)
	{
		perror ("error in tcsetattr");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
