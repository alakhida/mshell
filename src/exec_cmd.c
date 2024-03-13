#include "../includes/minishell.h"

static  void    free_ptr(char **ptr)
{
    int i;

    i = 0;
    while (ptr[i])
    {
        free(ptr[i]);
        i++;
    }
    free(ptr);
}

void    exec_cmd(t_cmd *cmds, t_env *env)
{
    int pid;
    t_env   *path_node;
    char    **path;
    char    *tmp_path;
    char    *holder;
    char    **envc;
    int     i;

    pid = 0;
    path_node = NULL;
    path = NULL;
    tmp_path = NULL;
    envc = NULL;
    holder = NULL;
    i = 0;
    while (cmds)
    {
        pid = fork();
        if (pid == 0)
        {
            path_node = ms_env_search("PATH", env);
            if (path_node)
            {
                path = ft_split(path_node->value, ':');
                while (path[i])
                {
                    tmp_path = ft_strjoin(ft_strdup(cmds->cmd[0]), path[i]);
                    if (access(tmp_path, F_OK) == 0)
                        break;
                    free(tmp_path);
                    i++;
                }
                free_ptr(path);
                if (tmp_path)
                {
                    envc = (char **)malloc((node_count(env) + 1) * sizeof(char *));
                    i = 0;
                    while (env)
                    {
                        holder = ft_strjoin(ft_strdup(env->varname), "=");
                        envc[i] = ft_strjoin(holder, env->value);
                        env = env->next;
                        i++;
                    }
                    envc[i] = NULL;
                    execve(cmds->cmd[0], cmds->cmd, envc);
                }
            }
            printf("no such file or directory\n");
            exit(1);
        }
        cmds = cmds->next;
    }
}