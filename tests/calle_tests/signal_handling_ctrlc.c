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
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
		;
}

int main( void )
{
	char	*line_from_terminal;
    struct	sigaction sa;

	sa.sa_handler = &handle_sig;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL); // For ctrl + c
    sigaction(SIGQUIT, &sa, NULL); /* For ctrl + \ */
	while (1)
	{
	    line_from_terminal = readline(" >  ");
	    add_history(line_from_terminal);
	    free(line_from_terminal);
	 }
	 return 0;
}
