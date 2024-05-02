#include "../includes/minishell.h"

bool    cmd_is_builtin(char *string)
{
    if (!ft_strcmp(string, "cd") || !ft_strcmp(string, "echo")
        || !ft_strcmp(string, "env") || !ft_strcmp(string, "unset")
        || !ft_strcmp(string, "export") || !ft_strcmp(string, "pwd")
        || !ft_strcmp(string, "exit"))
        return (true);
    else
        return (false);
}

bool    pipe_chain_present(t_cmd *cmds)
{
    int i;

    i = 0;
    while (cmds)
    {
        i++;
        cmds = cmds->next;
    }
    if (i == 1)
        return (false);
    else
        return (true);
}

char  *ft_strtok(char *str, const char *delim)
{
    static char *s = NULL;
    char *ret;
    int i;

    if (str)
        s = str;
    if (!s)
        return (NULL);
    i = 0;
    while (s[i])
    {
        if (ft_strchr(delim, s[i]))
        {
            s[i] = '\0';
            ret = s;
            s = s + i + 1;
            return (ret);
        }
        i++;
    }
    ret = s;
    s = NULL;
    return (ret);
}

char     *cmd_path(char *cmd, t_env *env)
{
    t_env  *curr; 
    char    *path;
    char    *dir;

    curr = env;
    if (!curr)
        return (NULL);
    while (curr)
    {
        if (ft_strcmp(curr->varname, "PATH") == 0)
            break;
        curr = curr->next;
    }
    path = ft_strdup(curr->value);
    dir = ft_strtok(path, ":");
     while (dir != NULL)
     {
   
        char *cmdpath = malloc(ft_strlen(dir) + ft_strlen(cmd) + 2);
        if (!cmdpath)
        {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        strcpy(cmdpath, dir);
        strcat(cmdpath, "/");
        strcat(cmdpath, cmd);
        if (access(cmdpath, X_OK) == 0)
        {
            free (path);
            path = cmdpath;
            free (cmdpath);
            break;
        }
        free(cmdpath);
        dir = ft_strtok(NULL, ":");
    }
    return path;
}

void    exec_cmd(t_env **env, t_cmd *cmds)
{
    bool    pipe_chain;
    char    *path;
    pid_t   child;
    int     pip[2];
    int     save_stdout;
    int     exit_status;
    t_cmd   *curr;

    pipe_chain = pipe_chain_present(cmds);
    curr = cmds;
    save_stdout = 0;
    path = cmd_path(cmds->cmd[0], *env);
    while (cmds)
    {
        if (cmd_is_builtin(cmds->cmd[0]) && !pipe_chain)
            exec_built_in(cmds, env);
        else if (path != NULL)
	    {
	        child = fork();
            pipe(pip);
            if (child == -1)
                exit(EXIT_FAILURE);
            if (child == 0)
            {
                dup2(save_stdout, STDIN_FILENO);
                if (save_stdout)
                    close(save_stdout);
                if (cmds->next)
                {
                    close(pip[0]);
                    dup2(pip[1], STDOUT_FILENO);
                    close(pip[1]);
                }
                if (execve(path, cmds->cmd, NULL) == -1)
                    exit(EXIT_FAILURE);
            }
            close(pip[1]);
            if (save_stdout)
                close(save_stdout);
            if (cmds->next)
                save_stdout = pip[0];
	    }
        cmds = cmds->next;
        if (cmds)
            path = cmd_path(cmds->cmd[0], *env);
    }
    while (curr)
    {
        waitpid(-1, &exit_status, WNOHANG);
        if (WIFSIGNALED(exit_status))
            printf("%i\n", WTERMSIG(exit_status));
        if (WIFEXITED(exit_status))
            curr = curr->next;
    }
}