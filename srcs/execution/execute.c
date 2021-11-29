# include "../../includes/minishell.h"

int select_builtin_test(int index, int argc, char **argv);

void    init_fds(int fd[100])
{
    int i;

    i = 0;
    while (i < 100)
    {
        fd[i] = -1;
        i++;
    }
}

void    close_fds(int fd[100])
{
    int i;

    i = 0;
    while (fd[i] != -1)
    {
        close(fd[i]);
        i++;
    }
}

void    free_command_block(char **command_block)
{
    int d;

    d = 0;
    while (command_block[d])
        free(command_block[d++]);
    free(command_block);
}

int execute_binary(char **command_block)
{
    char    *path;
    char	**clean_env;

    path = get_path(command_block);
    clean_env = ft_exported_vars('x');
    if ((execve(path, command_block, clean_env)) == -1)
    { 
        free(path);
        exit(EXIT_FAILURE);
    }
    exit (0); 
}

int close_used_fds(int (*fd)[2], int current)
{
    close(fd[current][0]);
    close(fd[current + 1][1]);
    return (0);
}

int close_unused_fds(int (*fd)[2], int current, int nb_cmds)
{
    int idx;
    int current_read;
    int current_write;
    int ret;

    idx = 0;
    ret = 0;
    current_read = current;
    current_write = current + 1;
    while (idx < nb_cmds)
    {
        if (idx != current_read)
            ret = close(fd[idx][0]);
        if (idx != current_write)
            ret = close(fd[idx][1]);
        if (ret < 0)
            return (0);
        idx++;
    }
    return (1);
}


int	make_pipes(int (*fd)[2], int size)
{
    int i;

    i = 0;
    while (i < size + 1)
    {
        if (pipe(fd[i]) < 0)
            return 1;
        i++;
    }
    return (0);
}

int	nb_cmds(char ***cmd)
{
    int n;

    n = 0;
    while (cmd[n])
        n++;
    return (n);
}

int check_if_file(char **cmd)
{
    int i;
    int d;
    int invalid_fd;
    int fd;

    i = 0;
    while (cmd[i])
    {
        d = 0;
        while (cmd[i][d])
        {
            if (cmd[i][d] == '/')
            {
                fd = open(cmd[i], O_RDWR);
                invalid_fd = check_fd(fd, cmd[i]);
                if (invalid_fd)
                    return (invalid_fd);
            }
            d++;
        }
        i++;
    }
    return (0);
}

int	execute_child(int (*fd)[2], int i, int n, char **cmd)
{
    int fds[100];
    init_fds(fds);
    t_redir redir;

    redir.cmd = cmd;
    if (fd)
    {
        close_unused_fds(fd, i, n);
        dup2(fd[i][0], STDIN_FILENO);
        if (i != n - 1)
            dup2(fd[i + 1][1], STDOUT_FILENO);

    }
    cmd = ft_redirect(&redir);
    remove_quotes_list(cmd);
    if (!check_if_file(cmd))
        execute_binary(cmd);
    else
        exit(127);
    close_fds(fds);
    if (fd)
    {
        close(fd[i][0]);
        close(fd[i + 1][1]);
    }
    return (0);
}

int     execute_builtin(int (*fd)[2], int i, int n, char **cmd)
{
    int ret;
    int fds[100];
    t_redir redir;

    redir.cmd = cmd;
    redir.es = 0;
    init_fds(fds);
    if (fd)
    {
        close_unused_fds(fd, i, n);
        dup2(fd[i][0], STDIN_FILENO);
        if (i != n - 1)
            dup2(fd[i + 1][1], STDOUT_FILENO);
    }
    redir.es = 0;
    redir.cmd = ft_redirect(&redir);
    remove_quotes_list(redir.cmd);
    ret = 1;
    if (redir.cmd[0] && !redir.es)
        ret = select_builtin_test(builtin_finder(redir.cmd[0]), strlen_list(redir.cmd), redir.cmd);
    close_fds(fds);
    if (fd)
    {
        close(fd[i][0]);
        close(fd[i + 1][1]);
    }
    free_str_list(redir.cmd, strlen_list(redir.cmd));
    if (fd)
        exit (ret);
    return (ret);
}

int wait_and_get_status()
{
    int status;
    int i;
    pid_t wpid;

    while ((wpid = wait(&status)) > 0)
        i = 1;
    if (WIFEXITED(status))
        status = WEXITSTATUS(status);
    (void)i;
    return (status);
}

int	ft_multipipes2(char ***cmd)
{
    int (*fd)[2];
    int i;
    int *pids;
    int status;
    int n;
    char **cmdcmp;

    n = nb_cmds(cmd);
    fd = malloc(sizeof(*fd) * (n + 1));
    pids = malloc(sizeof(int) * n);
    make_pipes(fd, n);
    i = -1;
    while (++i < n)
    {
        cmdcmp = str_list_dup(cmd[i]);
        cmdcmp = get_command(cmdcmp);
        pids[i] = fork();
        if (pids[i] == 0)
        {
            if (builtin_finder(cmdcmp[0]) == -1)
                execute_child(fd, i, n, cmd[i]);
            else
                status = execute_builtin(fd, i, n, cmd[i]);
        }
        free_list_and_return_null(cmdcmp, strlen_list(cmdcmp));
        free_list_and_return_null(cmd[i], strlen_list(cmd[i]));
    }
    close_unused_fds(fd, n + 1, n);
    status = wait_and_get_status();
    free(pids); 
    close(fd[n][1]);
    close(fd[n][0]);
    free(fd); 
    return (status);
}

int    execute(char ***command_block)
{
    char **cmdcmp;
    int pid;
    int status;
    int stdoutcpy = dup(STDOUT_FILENO);
    int stdincpy = dup(STDIN_FILENO);
    int fd[100];
    t_redir redir;

    init_fds(fd);
    status = 0;
    redir.cmd = command_block[0];
    if (command_block[0])
    {
        if (nb_cmds(command_block) > 1)
            return(ft_multipipes2(command_block));
        else
        {
            cmdcmp = str_list_dup(redir.cmd);
            cmdcmp = get_command(cmdcmp);
            if (builtin_finder(cmdcmp[0]) == -1)
            {
                pid = fork();

                if (pid == 0)
                    execute_child(NULL, 0, 1, redir.cmd);
                wait(&status);
                if (WIFEXITED(status))
                    status = WEXITSTATUS(status);
            }
            else
            {
                status = execute_builtin(NULL, 0 , 1, str_list_dup(redir.cmd));
                dup2(stdincpy, STDIN_FILENO);
                dup2(stdoutcpy, STDOUT_FILENO);
            }
            free_list_and_return_null(cmdcmp, strlen_list(cmdcmp));
            free_list_and_return_null(redir.cmd, strlen_list(redir.cmd));
        }
    }

    return (status);
}
