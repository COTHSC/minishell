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

int check_redirect_type(int redirect_type)
{
    if (redirect_type != 1 && redirect_type != 2 && redirect_type != 3 && redirect_type != 6)
    {
        ft_putstr_fd("minishell: syntax error near unexpected token '", 1);
        ft_putstr_fd("'\n", 1);
        return (0);
    }
    return (1);
}

char **make_heredoc(char **line_from_terminal)
{
    int i = 0;
    int d = 0;
    int pid;
    int fd[2];
    int redirect_type = 0;
    char *line;
    char *separator;

    while (line_from_terminal[i])
    {
        d = 0;
        while (line_from_terminal[i][d])
        {
            if (is_redirect(line_from_terminal[i][d]))
            {
                while (line_from_terminal[i] && is_redirect(line_from_terminal[i][d]))
                    redirect_type += is_redirect(line_from_terminal[i][d++]);
                if (redirect_type == 6)
                {
                    pipe(fd);
                    if (line_from_terminal[i][d])
                    {
                        separator = ft_strdup(&line_from_terminal[i][d]);
                    }

                    else 
                    {
                        separator = ft_strdup(line_from_terminal[i + 1]);
                        free(line_from_terminal[i + 1]);
                        line_from_terminal[i + 1] = ft_itoa(fd[0]);
                    }
                    pid = fork();
                    if (pid == 0)
                    {
                        close(fd[0]);
                        while (1)
                        {
                            ft_putstr_fd("< ", 1);
                            get_next_line(STDIN_FILENO, &line);
                            if (ft_strncmp(line, separator, ft_strlen(line)) || ft_strlen(line) == 0)
                            {
                                ft_putstr_fd(line, fd[1]);
                                ft_putstr_fd("\n", fd[1]);
                                free(line);
                            }
                            else
                            {
                                close(fd[1]);
                                free(line);
                                exit(0);
                            }
                        }
                    }
                    wait(NULL);
                    free(separator);
                    close(fd[1]);
                    return (line_from_terminal);
                }
            }
            d++;

        }
        i++;

    }
    return (line_from_terminal);

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

    if (!env[0])
        g_env = create_basic();
    else
        g_env = str_list_dup(env);
    init_env();
    commands = NULL;
    es = 0;
    ft_isalnum(1);
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
        command_list[0] = make_heredoc(command_list[0]);
        free_str_list(commands, strlen_list(commands));
        tmp_es = execute(command_list);
        if (tmp_es != exit_signal)
            es = tmp_es;
        free(command_list);
        free(line_from_terminal);
        if (!isatty(STDIN_FILENO))
            tmp_es = -1;
        if (tmp_es == -1)
        {
            free_str_list(g_env, strlen_list(g_env));
            break;
        }

    }
    return (es);
}
