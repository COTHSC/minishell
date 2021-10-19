/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 12:24:08 by calle             #+#    #+#             */
/*   Updated: 2021/10/19 18:18:22 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int	main(int argc, char **argv, char **env)
{
	(void)argv;
	if (argc != 1)
	{
		errno = 1;
		perror(NULL);
		return (EXIT_FAILURE);
	}
	int i = 0;
	while (env[i])
		printf("%s\n", env[i++]);
	return (EXIT_SUCCESS);
}
