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

static int	ft_ischar(char o, char c)
{
	if (o == c)
		return (1);
	return (0);
}

static int	ft_countthewords(char const *s, char c)
{
	int		i;
	int		cw;

	i = 0;
	cw = 0;
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c)
			cw++;
		i++;
	}
	if (i == 0)
		return (0);
	if (s[0] != c)
		cw++;
	if (s[i - 1] == c)
		cw--;
	return (cw);
}

static int	ftwtw(int len, char **strs, int row, const char *s)
{
	int		collumn;

	collumn = 0;
	while (collumn < len)
	{
		strs[row][collumn] = s[collumn];
		collumn++;
	}
	strs[row++][collumn] = '\0';
	return (row);
}

char	**ft_split(char const *s, char c)
{
	int		wc;
	char	**strs;
	int		lead;
	int		follow;
	int		row;

	row = 0;
	lead = 0;
	wc = ft_countthewords(s, c);
	strs = (char **)calloc((wc + 1), sizeof(char *));
	if (!strs)
		return (NULL);
	while (row < wc)
	{
		while (ft_ischar(s[lead], c))
			lead++;
		follow = lead;
		while (!ft_ischar(s[lead], c) && s[lead])
			lead++;
		strs[row] = (char *)malloc(sizeof(char) * ((lead - follow + 1)));
		if (!strs)
			return (NULL);
		row = ftwtw(lead - follow, strs, row, (s + follow));
	}
	return (strs);
}

struct termios *fetch_oldtio(void)
{
	static struct termios	oldtio;
	static int switch_off;

	if (!switch_off)
	{
		tcgetattr(STDIN_FILENO, &oldtio); //save terminal attributes
		switch_off = 1;
	}
	return &oldtio;
}

void handle_sig(int sig, siginfo_t *info, void *ucontext)
{
	int pid;

	pid = info->si_pid;
	printf("pid: %d\n", pid);
	printf("sig: %d\n", sig);
	if (pid != 0 && sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (pid != 0 && sig == SIGQUIT)
	{
		if (rl_point == 0)
		{
			write(1, "exit\n", 5);
		//	if (tcsetattr(STDIN_FILENO, TCSANOW, fetch_oldtio()) < 0) // restore terminal attr
		//		perror ("error in tcsetattr");
			exit(0);
		}
	}
}

void	signal_handler_settings(struct sigaction *sa)
{
	sa->sa_sigaction = &handle_sig;
	sa->sa_flags = SA_RESTART | SA_SIGINFO;
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
	//newtio->c_cc[VQUIT] = 255;
}

int	terminal_settings(struct termios *oldtio, struct termios *newtio)
{
	int	ret;

	fetch_oldtio();
	//ret = tcgetattr(STDIN_FILENO, oldtio); //save terminal attributes
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

int do_exec()
{
	int pid;
	const char *cmds[] = {"/usr/bin/cat", 0};
	pid = fork();

	if (pid == 0)
		execve("/usr/bin/cat", cmds, NULL);
	else
		wait(NULL);
	return (0);
}

int main( void )
{
	char	*line_from_terminal;
//	char	*cmds;
	//int	i;
    	struct	sigaction sa;
	struct	termios oldtio;
	struct	termios newtio;

	terminal_settings(&oldtio, &newtio);
	signal_handler_settings(&sa);
	while (1)
	{
		//i = 0;
		line_from_terminal = readline(" >  ");
		add_history(line_from_terminal);
		//cmds = ft_split(line_from_terminal, ' ');
		do_exec();
		//while (cmds(i))
		//	free(cmds[i]);
		free(line_from_terminal);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &oldtio); //restore terminal attributes
	return 0;
}
