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

char     *cmd_path(char *cmd, t_env *env)
{
    t_env  *curr; 
    char    *path;
    char    *dir;

    curr = env;
    while (curr)
    {
        if (ft_strcmp(curr->varname, "PATH") == 0)
            break;
        curr = curr->next;
    }
    if (!curr)
        return (NULL);
    path = ft_strdup(curr->value);
    dir = strtok(path, ":");
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
        dir = strtok(NULL, ":");
    }
    return path;
}

void    exec_cmd(t_env **env, t_cmd *cmds)
{
    bool    pipe_chain;
    char    *path;
    pid_t   child;

    pipe_chain = pipe_chain_present(cmds);
    path = cmd_path(cmds->cmd[0], *env);
    while (cmds)
    {
        child = fork();
        if (cmd_is_builtin(cmds->cmd[0]) && !pipe_chain)
            exec_built_in(cmds, env);
        execve(path, cmds->cmd,NULL);

        
        cmds = cmds->next;
    }
}