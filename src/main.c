/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calmouht <calmouht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 03:18:08 by calmouht          #+#    #+#             */
/*   Updated: 2024/04/15 17:14:38 by calmouht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int	ms_prompt(t_env *env)
// {
// 	char	*cmd;
// 	char	**lexed;
// 	t_cmd	*cmd2;

// 	cmd = readline("$> ");
// 	add_history(cmd);
// 	if (cmd == NULL)
// 		return (2);
// 	lexed = ms_parse(cmd);
// 	ms_rendercmd(lexed, env);
// 	cmd2 = ms_cmdgen(lexed);
// 	while (cmd2)
// 	{
// 		int i = 0;
// 		while(cmd2->cmd[i])
// 		{
// 			printf("%p\n", cmd2->cmd[i]);
// 			i++;
// 		}
// 		cmd2 = cmd2->next;
// 		cmd2->next = NULL;
// 	}
// 	(void)lexed;
// 	(void)env;
// 	return (0);
// }

	// while (cmd2)
	// {
	// 	int i = 0;
	// 	while(cmd2->cmd[i])
	// 	{
	// 		printf("\'%s\' \n", cmd2->cmd[i]);
	// 		i++;
	// 	}
	// 	// puts(":C===3");
	// 	cmd2 = cmd2->next;
	// }
	// // ms_errors(lexed);
	// (void)lexed;
int	ms_prompt(t_env **env)
{
	char	*cmd;
	char	**lexed;
	t_cmd	*cmd2;

	cmd = readline("$> ");
	add_history(cmd);
	if (cmd == NULL)
		return (2);
	lexed = ms_parse(cmd);
	ms_rendercmd(lexed, *env);
	cmd2 = ms_cmdgen(lexed);
	exec_cmd(env, cmd2);
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
