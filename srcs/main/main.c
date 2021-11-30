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

int is_in_quotes(char *str)
{
    if (str[0] == '\'' || str[ft_strlen(str) - 2] == '\'')
        return (1);
    if (str[0] == '"' || str[ft_strlen(str) - 2] == '"')
        return (2);
    return (0);
}

int check_redirect_type(int redirect_type)
{
    if (redirect_type != 1 && redirect_type != 2 && redirect_type != 3 && redirect_type != 6)
    {
        return (0);
    }
    return (1);
}

int main(int argc, char **argv, char **env)
{
    char **commands;
    int i;
    char ***command_list;
    char *line_from_terminal;
    int tmp_es;
    int es;
    int exit_signal = -1;
    (void)argc;
    (void)argv;
    
    init_minishell();
    if (!env[0])
        g_env = create_basic();
    else
        g_env = str_list_dup(env);
    init_env();
    commands = NULL;
    es = 0;
  //  ft_isalnum(1);
    while (1)
    {
        i = 0;
        if (isatty(STDIN_FILENO))
        {
            line_from_terminal = readline("💣-🐚 >  ");
            if (line_from_terminal)
                add_history(line_from_terminal);
        }

        else
            get_next_line(STDIN_FILENO, &line_from_terminal);
        if (check_syntax(line_from_terminal))
        {
            es = 2;
            free(line_from_terminal);
        }
        else
        {

            line_from_terminal = find_dollars(line_from_terminal, es);
            commands = ft_pipe_split(line_from_terminal);
            command_list = ft_calloc(sizeof(char ***) , 100);
            while (commands[i])
            {
                if (!is_empty(commands[i]))
                {
                    command_list[i] = ft_better_split(commands[i]);
                    command_list[i] = parse_declaration(command_list[i]);
                    command_list[i] = parse_block(command_list[i]);
                }
                i++;
            }
            free_str_list(commands, strlen_list(commands));
            tmp_es = execute(command_list);
            if (tmp_es != exit_signal)
                es = tmp_es;
            free(command_list);
            free(line_from_terminal);
        }
        if (!isatty(STDIN_FILENO))
            tmp_es = -1;
        if (tmp_es == -1)
        {
            free_str_list(g_env, strlen_list(g_env));
            break;
        }
    }
    reset_og_tio_settings();
    return (es);
}
