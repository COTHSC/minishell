#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <limits.h>
#include "../../includes/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

char **g_env;

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

    env4 = calloc_str_list(4);
    env4[0] = ft_strdup("PWD=");
    env4[1] = ft_strdup("OLDPWD");
    env4[2] = ft_strdup("SHLVL=");
    env4[3] = NULL;
    return (env4);
}

int is_empty(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (!ft_iswhitespace(str[i]))
            return (0);
        i++;
    }
    return (1);
}

int main(int argc, char **argv, char **env)
{
    char **command_blocks;
    int i;
    char ***command_block;
    char *line_from_terminal;
    int es;
    (void)argc;
    (void)argv;

    if (!env[0])
        g_env = create_basic();
    else
        g_env = str_list_dup(env);
    init_env();
    command_blocks = NULL;
    es = 0;
    while (1)
    {
        i = 0;
        line_from_terminal = readline(">  ");
	 add_history(line_from_terminal);
        line_from_terminal = find_dollars(line_from_terminal, es);
        command_blocks = ft_split(line_from_terminal, '|');
        command_block = ft_calloc(sizeof(char ***) , 100);
        while (command_blocks[i])
        {
            if (!is_empty(command_blocks[i]))
                command_block[i] = ft_better_split(command_blocks[i]);
            remove_quotes_list(command_block[i]);
            i++;
        }
        free_str_list(command_blocks, strlen_list(command_blocks));
        es = execute(command_block);
        free(line_from_terminal);
        i = 0;
        free(command_block);
        if (es == -14)
        {
            free_str_list(g_env, strlen_list(g_env));
            break;
        }
	if (!isatty(STDIN_FILENO))
		break;
    }
    return 0;
}
