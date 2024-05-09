/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhida <alakhida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 06:03:57 by alakhida          #+#    #+#             */
/*   Updated: 2024/05/09 04:22:19 by alakhida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*var_malloc(int j)
{
	char	*var;

	var = (char *)malloc((j + 1) * sizeof(char));
	if (!var)
		return (NULL);
	return (var);
}

char	*val_malloc(char *cmd, char *var, int j)
{
	int		i;
	char	*value;

	i = ft_strlen(cmd);
	if (i <= 0)
		return (NULL);
	value = (char *)malloc((i - j) * sizeof(char) + 1);
	if (!value)
	{
		free (var);
		return (NULL);
	}
	return (value);
}

char	*strdup_var(char *cmd, char *var, char *value)
{
	var = ft_strdup(cmd);
	if (!var)
		return (NULL);
	value = NULL;
	return (var);
}

void	export_to_list(t_env *current, char *var, char *value)
{
	while (current)
	{
		if (!ft_strcmp(var, current->varname))
		{
			free(current->value);
			current->value = value;
			free(var);
			break ;
		}
		else if (current->next == NULL)
		{
			current->next = add_node(var, value);
			break ;
		}
		current = current->next;
	}
}

char	*ft_strcpy_env(char *cmd, char *var, int j)
{
	var = var_malloc(j);
	if (!var)
		return (NULL);
	ft_strlcpy(var, cmd, j + 1);
	return (var);
}

char	*cpy_value(char *cmd, char *var, char *value, int j)
{
	int		i;

	i = ft_strlen(cmd);
	if (i <= 0)
		return (NULL);
	value = val_malloc(cmd, var, j);
	if (!value)
		return (NULL);
	ft_strlcpy(value, (cmd + j + 1), i - j + 1);
	return (value);
}

void	exporting(t_cmd *cmds, t_env **envp)
{
	int		i;
	t_env	*current;
	char	*var;
	char	*value;
	int		j;

	i = 1;
	current = *envp;
	while (cmds->cmd[i] != NULL)
	{
		j = ft_strchar(cmds->cmd[i], '=');
		if (j > 0)
		{
			var = ft_strcpy_env(cmds->cmd[i], var, j);
			value = cpy_value(cmds->cmd[i], var, value, j);
			export_to_list(current, var, value);
		}
		else if (j <= 0)
		{
			printf("%s: '%s': not a valid identifier\n",
				cmds->cmd[0], cmds->cmd[i]);
			return ;
		}
		i++;
	}
}

void	ft_export(t_cmd *cmds, t_env **envp)
{
	if (!cmds->cmd[1])
		ft_env_export(envp);
	else
		exporting(cmds, envp);
}