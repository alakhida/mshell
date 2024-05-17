/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calmouht <calmouht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 22:09:40 by alakhida          #+#    #+#             */
/*   Updated: 2024/05/17 05:49:56 by calmouht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_err(char token)
{
	ft_putstr_fd("syntax error near unexpected token .", 2);
	ft_putchar_fd(token, 2);
	ft_putendl_fd(".", 2);
}

int	pre_syntax_check(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '|' && str[i + 1] && str[i + 1] == '|')
		{
			print_err(str[i]);
			return (1);
		}
		i++;
	}
	i--;
	while (i >= 0 && (str[i] == ' ' || str[i] == '\t'))
		i--;
	if (str[i] == '|')
	{
		print_err(str[i]);
		return (1);
	}
	return (0);
}

void	free_all(t_cmd *cmd)
{
	t_cmd	*tmp;
	t_red	*tmp2;

	while (cmd)
	{
		tmp = cmd;
		if (cmd->cmd)
			free_dbl_ptr(cmd->cmd);
		while (cmd->red)
		{
			tmp2 = cmd->red;
			if (cmd->red)
			{
				if (cmd->red->file)
					free(cmd->red->file);
			}
			cmd->red = cmd->red->next;
			free(tmp2);
		}
		cmd = cmd->next;
		free(tmp);
	}
}

char	**fix_args(char **args)
{
	int	i;

	i = 0;
	while (args && args[i])
	{
		if (count_var(args[i], SINGLE_Q) > 0 || count_var(args[i],
				DOUBLE_Q) > 0)
		{
			if (count_var(args[i], SINGLE_Q) % 2 != 0 || count_var(args[i],
					DOUBLE_Q) % 2 != 0)
			{
				write(2, "syntax error\n", 14);
				free_dbl_ptr(args);
				return (NULL);
			}
			else
				remove_q(args[i]);
		}
		i++;
	}
	return (args);
}
