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

int    count_pipes(t_cmd *cmds)
{
    int i;

    i = 0;
    while (cmds)
    {
        i++;
        cmds = cmds->next;
    }
    return (i);
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

// void	exec_pipes(t_cmd *cmds)
// {
// 	int		pip[2];
// 	// pid_t	child;

// 			puts("hh");
//     while (cmds)
//     {
// 		// child = fork();
//     	pipe(pip);
// 		// if (child == 0)
// 		// {
// 			close(pip[1]);
// 			if (dup2(pip[0], STDIN_FILENO) < 0)
// 			{
// 				printf("couldn't get input\n");
// 				return ;
// 			}
//     // close (pip[1]);
// 	// dup2(pip[1], STDOUT_FILENO);
//    		// }
// 	// close(pip[1]);
//     //    if (cmds->next != NULL)
//     //         dup2(pip[1], STDOUT_FILENO);
//     // close(pip[0]);
//     cmds = cmds->next;
//     }
// }
void    exec_cmd(t_env **env, t_cmd *cmds)
{
    bool    pipe_chain;
    char    *path;
    pid_t   child;
    int     pip[2];
    int     save_stdout;
    t_cmd   *curr;

    pipe_chain = pipe_chain_present(cmds);
    curr = cmds;
    save_stdout = 0;
     while (cmds)
    {
        path = cmd_path(cmds->cmd[0], *env);
        if (path == NULL)
        {
            printf("Command not found: %s\n", cmds->cmd[0]);
            cmds = cmds->next;
            continue;
        }
        if (cmd_is_builtin(cmds->cmd[0]) && !pipe_chain)
            exec_built_in(cmds, env);
        else
        {
            if (pipe_chain && cmds->next)
                pipe(pip);
            child = fork();
            if (child == -1)
                exit(EXIT_FAILURE);
            if (child == 0)
            {
                if (pipe_chain && cmds->next)
                {
                    close(pip[0]);
                    dup2(pip[1], STDOUT_FILENO);
                    close(pip[1]);
                }
                if (save_stdout)
                {
                    dup2(save_stdout, STDIN_FILENO);
                    close(save_stdout);
                }
                if (execve(path, cmds->cmd, NULL) == -1)
                    exit(EXIT_FAILURE);
            }
            if (pipe_chain && cmds->next)
            {
                close(pip[1]);
                save_stdout = pip[0];
            }
        }
        cmds = cmds->next;
    }
    while (wait(&child) > 0);
}