# include "../../includes/minishell.h"

static void modify_terminal_attributes(struct termios *newtio)
{
	newtio->c_lflag &= ~(ICANON);
	newtio->c_lflag |= ICANON; // Set terminal in canonical
	newtio->c_lflag &= ~(ISIG);
	newtio->c_lflag |= ISIG; // Set signal handling options
	newtio->c_lflag &= ~(ECHOCTL); // Unset ctrl + <char> printing
	newtio->c_cc[VQUIT] = 4; // Rewire SIGQUIT to ctrl + D
}

static int set_terminal_attributes(struct termios *newtio)
{
    int ret;

	modify_terminal_attributes(newtio);
	ret = tcsetattr(STDIN_FILENO, TCSANOW, newtio); //update current terminal attributes
	if (ret < 0)
	{
		perror ("error in tcsetattr");
		return (EXIT_FAILURE);
	}
    else
        return (EXIT_SUCCESS);
}

int	terminal_settings(void)
{
	int	ret;

    if (!isatty(STDIN_FILENO))
        return (EXIT_SUCCESS);
    else if (!setch_og_tio(0))
        return (EXIT_FAILURE);
    ret = set_terminal_attributes(setch_parent_tio(0));
	return (ret);
}
