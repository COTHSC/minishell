#include "../../includes/minishell.h"

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
    char buf[PATH_MAX];
    char *cwd;

    cwd = ft_strdup(getcwd(buf, PATH_MAX));
    env4 = calloc_str_list(4);
    env4[0] = ft_strjoin("PWD=", cwd);
    env4[1] = ft_strdup("OLDPWD");
    env4[2] = ft_strdup("SHLVL=");
    env4[3] = NULL;
    free(cwd);
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
    char **commands;
    int i;
    char ***command_list;
    char *line_from_terminal;
    int es;
    (void)argc;
    (void)argv;

    if (!env[0])
        g_env = create_basic();
    else
        g_env = str_list_dup(env);
    init_env();
    commands = NULL;
    es = 0;
    while (1)
    {
        i = 0;
        if (isatty(STDIN_FILENO))
            line_from_terminal = readline(">  ");
        else
            get_next_line(STDIN_FILENO, &line_from_terminal);
        add_history(line_from_terminal);
        line_from_terminal = find_dollars(line_from_terminal, es);
        commands = ft_split(line_from_terminal, '|');
        command_list = ft_calloc(sizeof(char ***) , 100);
        while (commands[i])
        {
            if (!is_empty(commands[i]))
            {
                command_list[i] = ft_better_split(commands[i]);
                remove_quotes_list(command_list[i]);
            }
            i++;
        }
        free_str_list(commands, strlen_list(commands));
        es = execute(command_list);
        free(command_list);
        free(line_from_terminal);
        if (!isatty(STDIN_FILENO))
            es = -14;
        if (es == -14)
        {
            free_str_list(g_env, strlen_list(g_env));
            break;
        }

    }
    return 0;
}
