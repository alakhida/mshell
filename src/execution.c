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

void    exec_cmd(t_env **env, t_cmd *cmds)
{
    bool    pipe_chain;

    pipe_chain = pipe_chain_present(cmds);
    while (cmds)
    {
        if (cmd_is_builtin(cmds->cmd[0]) && !pipe_chain)
        {
            check_built_in(cmds, env);
        }
        cmds = cmds->next;
    }
}