#include "../../includes/minishell.h"
#include <fcntl.h>
#include <limits.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <termios.h>
#include <unistd.h>

char **g_env;

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
    return (EXIT_SUCCESS);
}

void    set_to_null(char *var);

void    remove_quotes_list(char **command_block)
{
    int i;
    char *temp;

    i = 0;
    while (command_block[i])
    {
        temp =  remove_quotes(command_block[i]);
        command_block[i] = temp;
        i++;
    }
}

char **create_basic()
{
    char **env4;

    env4 = (char **)malloc(3 * sizeof(char*));
    env4[0] = ft_strdup("PWD=");
    env4[1] = ft_strdup("OLDPWD=");
    env4[2] = ft_strdup("SHLVL=");
    return (env4);
}


int main(int argc, char **argv, char **env)
{
    char **env2;

    (void)argc;
    (void)argv;
    //char **command_block;
    int es;
    char *line_from_terminal;

    struct	sigaction sa;
	struct	termios oldtio;
	struct	termios newtio;

	terminal_settings(&oldtio, &newtio);
	signal_handler_settings(&sa);
    if (!env[0])
        g_env = create_basic();
    else
        g_env = str_list_dup(env);
//    init_env();
    es = 0;
    while (1)
    {
		line_from_terminal = readline(" >  ");
        add_history(line_from_terminal);
        //line_from_terminal = find_dollars(line_from_terminal, es);
        //command_block = ft_better_split(line_from_terminal);
        //remove_quotes_list(command_block);
        //es = execute(command_block);
        free(line_from_terminal);
        //free_command_block(command_block);
    }
	tcsetattr(STDIN_FILENO, TCSANOW, &oldtio); //restore terminal attributes
    free_str_list(env2, strlen_list(g_env));
    return 0;
}
