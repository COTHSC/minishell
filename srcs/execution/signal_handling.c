# include "../../includes/minishell.h"

static void    put_newline(void)
{
		write(1, "\n", 1);
		rl_on_new_line();
}

static void handle_sig(int sig, siginfo_t *info, void *ucontext)
{
    (void)ucontext;

    printf("pid: %d\n", info->si_pid);
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
			if (tcsetattr(STDIN_FILENO, TCSANOW, setch_og_tio(1)) < 0)
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
	sigaction(SIGINT, sa, NULL);
    sigaction(SIGQUIT, sa, NULL);
}
