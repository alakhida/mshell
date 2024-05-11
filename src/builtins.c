/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhida <alakhida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 03:29:33 by alakhida          #+#    #+#             */
/*   Updated: 2024/05/11 12:00:09 by alakhida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strchar(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i] && s[i] != c)
	{
		if (s[i] == c)
			break ;
		i++;
	}
	return (i);
}

t_env	*add_node(char *var, char *value)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	new->varname = var;
	new->value = value;
	new->next = NULL;
	return (new);
}

int	is_digit(char *str)
{
	int		i;

	i = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
		i++;
	if (str[i] == '\0')
		return (0);
	else 
		return (1);
}

int	ft_exit(t_cmd *cmds)
{
	int		ex;

	ex = 0;
	if (!cmds->cmd[1])
		exit(0);
	if (cmds->cmd[2])
	{
		printf("too many argument\n");
		exit(ex);
	}
	if (!is_digit(cmds->cmd[1]))
	{
		ex = ft_atoi(cmds->cmd[1]);
		printf("exiting...\n");
		exit(ex);
	}
	if (is_digit(cmds->cmd[1]))
	{
		printf("%s: numeric argument required\n", cmds->cmd[1]);
		exit(1);
	}
	return (0);
}

int	exec_built_in(t_cmd *cmds, t_env **envp)
{
	if (!cmds->next)
		handle_redirections(cmds);
	if (!ft_strncmp(cmds->cmd[0], "echo", 4))
		ft_echo(cmds);
	else if (!ft_strncmp(cmds->cmd[0], "env", 3))
		ft_env(envp);
	else if (!ft_strncmp(cmds->cmd[0], "pwd", 3))
		ft_pwd(cmds);
	else if (!ft_strncmp(cmds->cmd[0], "export", 6))
		ft_export(cmds, envp);
	else if (!ft_strncmp(cmds->cmd[0], "unset", 5))
		ft_unset(cmds, envp);
	else if (!ft_strncmp(cmds->cmd[0], "cd", 2))
		ft_cd(cmds, envp);
	else if (!ft_strncmp(cmds->cmd[0], "exit", 4))
		ft_exit(cmds);
	return (0);
}
