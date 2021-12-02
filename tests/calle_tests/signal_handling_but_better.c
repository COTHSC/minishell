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

struct termios *setch_oldtio(int switch_off)
{
	static struct termios	oldtio;
    int                     ret;

	if (!switch_off)
	{
		ret = tcgetattr(STDIN_FILENO, &oldtio); //save terminal attributes
	    if (ret < 0)
	    {
		    perror ("error in tcgetattr");
		    return (NULL);
	    }
	}
	return (&oldtio);
}

struct termios *setch_parent_io(int switch_off)
{
	static struct termios	newtio;
    int                     ret;

	if (!switch_off)
	{
		ret = tcgetattr(STDIN_FILENO, &newtio); //save terminal attributes
	    if (ret < 0)
	    {
		    perror ("error in tcgetattr");
		    return (NULL);
	    }
	}
	return (&newtio);
}

static void modify_terminal_attributes(struct termios *newtio)
{
	newtio->c_lflag &= ~(ICANON);
	newtio->c_lflag |= ICANON; // Set terminal in canonical
	newtio->c_lflag &= ~(ISIG);
	newtio->c_lflag |= ISIG; // Set signal handling options
	newtio->c_lflag &= ~(ECHOCTL); // Unset ctrl + <char> printing
	newtio->c_cc[VQUIT] = 4; // Rewire SIGQUIT to ctrl + D
}

int	terminal_settings(void)
{
	int	ret;

	if(!setch_oldtio(0))
        return (EXIT_FAILURE);
    ret = set_terminal_attributes(setch_parent_io(0));
	return (ret);
}

int reset_og_tio_settings(void)
{
    int ret;

	ret = tcsetattr(STDIN_FILENO, TCSANOW, setch_oldtio(1)); //update current terminal attributes
    if (ret < 0)
	{
		perror ("error in tcsetattr");
		return (EXIT_FAILURE);
	}
	//printf("TERMIOS SETTINGS RESET \n");
	return (EXIT_SUCCESS);
}

int reset_parent_io_settings(void)
{
    int ret;

	ret = tcsetattr(STDIN_FILENO, TCSANOW, setch_parent_io(1)); //update current terminal attributes
    if (ret < 0)
	{
		perror ("error in tcsetattr");
		return (EXIT_FAILURE);
	}
	//printf("TERMIOS SETTINGS RESET \n");
	return (EXIT_SUCCESS);
}
int set_terminal_attributes(struct termios *newtio)
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

void    put_newline(void)
{
		write(1, "\n", 1);
		rl_on_new_line();
}

void handle_sig(int sig, siginfo_t *info, void *ucontext)
{
    (void)ucontext;

	if (info->si_pid != 0 && sig == SIGINT)
	{
		write(1, "^", 1);
		write(1, "C", 1);
        put_newline();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (info->si_pid == 0 && sig == SIGINT)
        put_newline();
	if (info->si_pid != 0 && sig == SIGQUIT)
	{
		if (rl_point == 0)
		{
			write(1, "exit\n", 5);
			if (tcsetattr(STDIN_FILENO, TCSANOW, setch_oldtio(1)) < 0) // restore terminal attr
				perror ("error in tcsetattr");
			exit(0);
		}
	}
	if (info->si_pid == 0 && sig == SIGQUIT)
    {
		write(1, "QUIT", 4);
        put_newline();
    }
}

void	signal_handler_settings(struct sigaction *sa)
{
	sa->sa_sigaction = &handle_sig;
	sa->sa_flags = SA_RESTART | SA_SIGINFO;
	sigaction(SIGINT, sa, NULL); // For ctrl + c
    sigaction(SIGQUIT, sa, NULL); /* For ctrl + \ */
}

int do_exec()
{
	int pid;
	char *cmds[] = {"/usr/bin/sleep", "5", 0};
    int exit_status;

    exit_status = 0;
	pid = fork();
	if (pid == 0)
    {
        reset_og_tio_settings();
		execve(cmds[0], cmds, NULL);
    }
	else
    {
		wait(&exit_status);
        reset_parent_io_settings();
    }
    if (WIFEXITED(exit_status))                                                                  
         exit_status = WEXITSTATUS(exit_status);
    //printf("Exit status: %d\n", exit_status);
	return (0);
}

int main( void )
{
	char	*line_from_terminal;
//	char	*cmds;
	//int	i;

	terminal_settings();
	signal_handler_settings(&sa);
	while (1)
	{
		//i = 0;
		line_from_terminal = readline(" >  ");
		add_history(line_from_terminal);
		//cmds = ft_split(line_from_terminal, ' ');
        //printf("line: %s\n", line_from_terminal);
		do_exec();
		//while (cmds(i))
		//	free(cmds[i]);
		free(line_from_terminal);
	}
    reset_og_tio_settings();
	return 0;
}
