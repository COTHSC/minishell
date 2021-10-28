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

void    readline_loop(char ***env)
{
    char **command_block;
    char *line_from_terminal;
    int es;

    es = 0;
    while (1)
    {
        line_from_terminal = readline(" >  ");
        add_history(line_from_terminal);
        line_from_terminal = find_dollars(line_from_terminal, es);
        command_block = ft_better_split(line_from_terminal);
        remove_quotes_list(command_block);
        es = execute(command_block, env);
        free(line_from_terminal);
        free_command_block(command_block);
    }
}

int main(int argc, char **argv, char **env)
{
    char **env2;

    (void)argc;
    (void)argv;

    env2 = str_list_dup(env);
    init_env(env2);
    ft_exported_vars(env2);
   // readline_loop(&env2);
    char **command_block;
     char *line_from_terminal;
     int es;

     es = 0;
     while (1)
     {
         line_from_terminal = readline(" >  ");
         add_history(line_from_terminal);
         line_from_terminal = find_dollars(line_from_terminal, es);
         command_block = ft_better_split(line_from_terminal);
         remove_quotes_list(command_block);
         es = execute(command_block, &env2);
         free(line_from_terminal);
         free_command_block(command_block);
     }
    free_str_list(env2, strlen_list(env2));
    return 0;
}
