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

int main( void ) {

struct	termios oldtio;
struct	termios newtio;
//struct	termios saved_in_settings;
//struct	termios saved_out_settings;
//struct	termios new_in_settings;
//struct	termios new_out_settings;
char	*line_from_terminal;

if (!isatty(STDIN_FILENO)) { exit(EXIT_FAILURE); }

	tcgetattr(STDIN_FILENO, &oldtio); //save terminal attributes
	tcgetattr(STDIN_FILENO, &newtio); //save terminal attributes
//	tcgetattr(STDIN_FILENO, &saved_in_settings); //save terminal attributes
//	tcgetattr(STDIN_FILENO, &new_in_settings); //retrieve current terminal attributes
//	tcgetattr(STDIN_FILENO, &saved_out_settings); //save terminal attributes
//	tcgetattr(STDIN_FILENO, &new_out_settings); //retrieve current terminal attributes
//	new_out_settings.c_lflag &= ~(ISIG);
//	new_in_settings.c_lflag &= ~(ISIG);
	newtio.c_lflag &= ~(ISIG);
	newtio.c_lflag |= ISIG;
	printf("VINTR: %hhu\n", newtio.c_cc[VINTR]);
	newtio.c_cc[VINTR] = 4;
	newtio.c_cc[VQUIT] = 255;
	printf("VINTR: %hhu\n", newtio.c_cc[VINTR]);
//	newtio.c_lflag &= ~(ECHO);
//	newtio.c_lflag &= ~(ECHONL);
//	newtio.c_lflag |= ECHONL;
//	tcsetattr(STDIN_FILENO, TCSANOW, &newtio); //update current terminal attributes
//	tcsetattr(STDIN_FILENO, TCSANOW, &new_in_settings); //update current terminal attributes
//	tcsetattr(STDIN_FILENO, TCSANOW, &new_out_settings); //update current terminal attributes
    while (1)
    {
        line_from_terminal = readline(" >  ");
        add_history(line_from_terminal);
        free(line_from_terminal);
    }
	tcsetattr(STDIN_FILENO, TCSANOW, &newtio); //restore terminal attributes
//	tcsetattr(STDIN_FILENO, TCSANOW, &new_in_settings); //restore terminal attributes
//	tcsetattr(STDIN_FILENO, TCSANOW, &new_out_settings); //restore terminal attributes
    return 0;
}
