#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <termios.h>

void handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		//rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		if (rl_point == 0)
		{
			write(1, "exit\n", 5);
			exit(0);
		}
	}
}

void	signal_handler_settings(struct sigaction *sa)
{
	sa->sa_handler = &handle_sig;
	sa->sa_flags = SA_RESTART;
	sigaction(SIGINT, sa, NULL); // For ctrl + c
    sigaction(SIGQUIT, sa, NULL); /* For ctrl + \ */
}


void	set_terminal_options(struct termios *newtio)
{
	newtio->c_lflag &= ~(ICANON); 
	newtio->c_lflag |= ICANON; // Set terminal in canonical
	newtio->c_lflag &= ~(ISIG);
	newtio->c_lflag |= ISIG; // Set signal handling options
	newtio->c_lflag &= ~(ECHOCTL); // Unset ctrl + <char> printing
	newtio->c_cc[VQUIT] = 4; // Rewire SIGQUIT to ctrl + D
}

int	terminal_settings(struct termios *oldtio, struct termios *newtio)
{
	int	ret;

	ret = tcgetattr(STDIN_FILENO, oldtio); //save terminal attributes
	if (ret < 0)
    {
      perror ("error in tcgetattr");
      return (EXIT_FAILURE);
    }
	ret = tcgetattr(STDIN_FILENO, newtio); //fetch terminal attributes
	if (ret < 0)
    {
      perror ("error in tcgetattr");
      return (EXIT_FAILURE);
    }
	set_terminal_options(newtio);
	ret = tcsetattr(STDIN_FILENO, TCSANOW, newtio); //update current terminal attributes
	if (ret < 0)
    {
      perror ("error in tcsetattr");
      return (EXIT_FAILURE);
    }
	printf("TERMIOS SETTINGS DONE \n");
    return (EXIT_SUCCESS);
}

int main( void )
{
	char	*line_from_terminal;
    struct	sigaction sa;
	struct	termios oldtio;
	struct	termios newtio;

	terminal_settings(&oldtio, &newtio);
	signal_handler_settings(&sa);
	while (1)
	{
	    line_from_terminal = readline(" >  ");
	    add_history(line_from_terminal);
	    free(line_from_terminal);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &oldtio); //restore terminal attributes
	return 0;
}
