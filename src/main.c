/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhida <alakhida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 03:18:08 by calmouht          #+#    #+#             */
/*   Updated: 2024/05/18 00:57:13 by alakhida         ###   ########.fr       */
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

int	ms_prompt(t_env **env, int *exit_status)
{
	char	*cmd;
	char	**lexed;
	char	**tmp;
	t_cmd	*cmd2;
	t_norm	index;

	cmd = readline("M0NG14L170_6-9$: ");
	if (cmd == NULL)
		return (2);
	add_history(cmd);
	if ((is_tab(cmd) == 1 || ft_strlen(cmd) < 1) || pre_syntax_check(cmd) != 0)
		return (free(cmd), 0);
	lexed = ms_parse(cmd);
	if (check_errors(lexed) == 1)
		return (free_dbl_ptr(lexed), free(cmd), 0);
	lexed = fix_args(lexed);
	if (lexed == NULL)
		return (free(cmd), 0);
	ms_rendercmd(lexed, *env, exit_status, &index);
	cmd2 = ms_cmdgen(lexed);
	if (sear(&cmd2) == 1)
		return (free(cmd), free_dbl_ptr(lexed), free_all(cmd2), 0);
	exec_cmd(env, cmd2, exit_status);
	return (free(cmd), free_dbl_ptr(lexed), free_all(cmd2), 0);
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
		g_signal_number = 0;
		cmd_status = ms_prompt(&env, &exit_status);
		if (cmd_status != 0)
			return (cmd_status);
		if (g_signal_number)
			exit_status = g_signal_number + 128;
		update_exit(&env, exit_status);
	}
}
