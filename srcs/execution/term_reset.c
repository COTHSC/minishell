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
