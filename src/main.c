/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhida <alakhida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 03:18:08 by calmouht          #+#    #+#             */
/*   Updated: 2024/05/11 07:51:11 by alakhida         ###   ########.fr       */
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

int	ms_prompt(t_env **env)
{
	char	*cmd;
	char	**lexed;
	t_cmd	*cmd2;

	cmd = readline("$> ");
	add_history(cmd);
	if (cmd == NULL)
		return (2);
	if (is_tab(cmd) == 1 || ft_strlen(cmd) == 0)
	{
		return (0);
	}
	lexed = ms_parse(cmd);
	ms_rendercmd(lexed, *env);
	cmd2 = ms_cmdgen(lexed);
	exec_cmd(env, cmd2);
	ms_errors(lexed);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int		cmd_status;
	t_env	*env;

	(void)argv;
	(void)argc;
	if (envp == NULL)
		return (EXIT_FAILURE);
	env = ms_env_new(envp);
	while (true)
	{
		cmd_status = ms_prompt(&env);
		if (cmd_status != 0)
			return (cmd_status);
	}
}
