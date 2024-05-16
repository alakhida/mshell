/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhida <alakhida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 03:18:08 by calmouht          #+#    #+#             */
/*   Updated: 2024/05/16 19:50:42 by alakhida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_tab(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

int	count_var(char *str, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

void	remove_q(char *str)
{
	char	*tmp;
	int		i;
	int		j;
	char	qtype;

	tmp = ft_calloc(sizeof(char) * (ft_strlen(str) + 1), 1);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == SINGLE_Q || str[i] == DOUBLE_Q)
		{
			qtype = str[i++];
			while (str[i] && str[i] != qtype)
				tmp[j++] = str[i++];
			if (str[i])
				i++;
		}
		else
			tmp[j++] = str[i++];
	}
	ft_strcpy(str, tmp);
	free(tmp);
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
void	free_cmd(char **av)
{
	char	**temp;

	temp = av;
	while (*av)
	{
		free(*av);
		av++;
	}
	av = temp;
	free(av);
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

int	sear(t_cmd **hh)
{
	t_cmd	*curr;

	curr = *hh;
	while (curr)
	{
		if (curr->flag == 1)
			return (1);
		curr = curr->next;
	}
	return (0);
}

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

int	ms_prompt(t_env **env, int *exit_status)
{
	char	*cmd;
	char	**lexed;
	char	**tmp;
	t_cmd	*cmd2;

	cmd = readline("M0NG14L170_6-9$: ");
	if (cmd == NULL)
		return (2);
	add_history(cmd);
	if ((is_tab(cmd) == 1 || ft_strlen(cmd) == 0) && pre_syntax_check(cmd))
		return (free(cmd), 0);
	lexed = ms_parse(cmd);
	if (check_errors(lexed) == 1)
		return (free_dbl_ptr(lexed),free(cmd), 0);
	ms_rendercmd(lexed, *env, exit_status);
	lexed = fix_args(lexed);
	if (lexed == NULL)
		return (free(cmd), 0);
	cmd2 = ms_cmdgen(lexed);
	if (sear(&cmd2) == 1)
		return (free(cmd), 0);
	ms_errors(lexed);
	exec_cmd(env, cmd2, exit_status);
	return (free(cmd),free_dbl_ptr(lexed), free_all(cmd2),  0);
}

int	main(int __unused argc, char __unused **argv, char **envp)
{
	int					cmd_status;
	int					exit_status;
	t_env				*env;

	signal(SIGINT, sig);
	signal(SIGQUIT, SIG_IGN);
	if (envp == NULL)
		return (EXIT_FAILURE);
	env = ms_env_new(envp);
	while (true)
	{
		signal_number = 0;
		cmd_status = ms_prompt(&env, &exit_status);
		if (cmd_status != 0)
			return (cmd_status);
		if (signal_number)
			exit_status = signal_number + 128;
		update_exit(&env, exit_status);
	}
}

//ls -la | cat -e >> gdgk > wh