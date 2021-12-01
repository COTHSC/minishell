# include "../../includes/minishell.h"

static int set_parent_attributes(struct termios *parent_tio)
{
    int ret;

	parent_tio->c_lflag &= ~(ICANON);
	parent_tio->c_lflag |= ICANON; // Set terminal in canonical
	parent_tio->c_lflag &= ~(ISIG);
	parent_tio->c_lflag |= ISIG; // Set signal handling options
	parent_tio->c_lflag &= ~(ECHOCTL); // Unset ctrl + <char> printing
    parent_tio->c_cc[VQUIT] = 4; // Rewire SIGQUIT to ctrl + D
	ret = tcsetattr(STDIN_FILENO, TCSANOW, parent_tio); //update current terminal attributes
	if (ret < 0)
	{
		perror ("error in tcsetattr");
		return (EXIT_FAILURE);
	}
    else
        return (EXIT_SUCCESS);
}

static int set_hd_attributes(struct termios *hd_tio)
{
    int ret;

	hd_tio->c_lflag &= ~(ICANON);
	hd_tio->c_lflag |= ICANON; // Set terminal in canonical
	hd_tio->c_lflag &= ~(ISIG);
	hd_tio->c_lflag |= ISIG; // Set signal handling options
	hd_tio->c_lflag &= ~(ECHOCTL); // Unset ctrl + <char> printing
    hd_tio->c_cc[VQUIT] = 0; // Rewire SIGQUIT to ctrl + D
	ret = tcsetattr(STDIN_FILENO, TCSANOW, hd_tio); //update current terminal attributes
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
    if (!setch_og_tio(0))
        return (EXIT_FAILURE);
    if (!setch_parent_tio(0)) 
        return (EXIT_FAILURE);
    if (!setch_hd_tio(0)) 
        return (EXIT_FAILURE);
    ret = set_parent_attributes(setch_parent_tio(1));
    if (ret == EXIT_FAILURE)
        return (ret);
    ret = set_hd_attributes(setch_hd_tio(1));
	return (ret);
}
