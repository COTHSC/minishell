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

int main( void )
{
struct	termios oldtio;
struct	termios newtio;
char	*line_from_terminal;

if (!isatty(STDIN_FILENO)) { exit(EXIT_FAILURE); }

	tcgetattr(STDIN_FILENO, &oldtio); //save terminal attributes
	tcgetattr(STDIN_FILENO, &newtio); //save terminal attributes
	newtio.c_lflag &= ~(ISIG);
	newtio.c_lflag |= ISIG;
	printf("VINTR: %hhu\n", newtio.c_cc[VINTR]);
	newtio.c_cc[VINTR] = 4;
	newtio.c_cc[VQUIT] = 255;
	printf("VINTR: %hhu\n", newtio.c_cc[VINTR]);
	tcsetattr(STDIN_FILENO, TCSANOW, &newtio); //update current terminal attributes
    while (1)
    {
        line_from_terminal = readline(" >  ");
        add_history(line_from_terminal);
        free(line_from_terminal);
    }
	tcsetattr(STDIN_FILENO, TCSANOW, &newtio); //restore terminal attributes
    return 0;
}
