/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calmouht <calmouht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 03:18:08 by calmouht          #+#    #+#             */
/*   Updated: 2024/05/14 05:07:24 by calmouht         ###   ########.fr       */
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

#define SINGLE_Q 39
#define DOUBLE_Q 34
#define NO_Q 0

// typedef struct _container{
// 	char **ptr;
// 	// int type ;
// 	struct _container *next;
// } _container;

// _container *creat_container(char **args)
// {
// 	_container *container;
// 	container = malloc(sizeof(_container));
// 	container->ptr = args;
// 	return (container);
// }

void	remove_q(char *str)
{
	char	*tmp;
	int		i;
	int		j;

	tmp = malloc(sizeof(char) * (strlen(str) + 1));
	if (tmp == NULL)
		return ;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == SINGLE_Q)
		{
			i++;
			while (str[i] && str[i] != SINGLE_Q)
				tmp[j++] = str[i++];
			if (str[i])
				i++;
		}
		else if (str[i] == DOUBLE_Q)
		{
			i++;
			while (str[i] && str[i] != DOUBLE_Q)
				tmp[j++] = str[i++];
			if (str[i])
				i++;
		}
		else
			tmp[j++] = str[i++];
	}
	tmp[j] = '\0';
	strcpy(str, tmp);
	free(tmp);
}

char	**fix_args(char **args)
{
	int	i;

	// _container * container = NULL;
	// _container *head =  container;
	// char **new_args;
	i = 0;
	// char **tmp;
	while (args && args[i])
	{
		if (count_var(args[i], SINGLE_Q) > 0 || count_var(args[i],
				DOUBLE_Q) > 0)
		{
			if (count_var(args[i], SINGLE_Q) % 2 != 0 || count_var(args[i],
					DOUBLE_Q) % 2 != 0)
			{
				write(2, "syntax err\n", 12);
				exit(1);
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

	while (cmd)
	{
		tmp = cmd;
		if (cmd->cmd)
			free_cmd(cmd->cmd);
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
		{
			return (1);
			/* code */
		}
		curr = curr->next;
		/* code */
	}
	return (0);
}

int	pre_syntax_check(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '|' && str[i + 1] && str[i + 1] == '|')
		{
			write(2, "syntax err : | \n", 17);
			return (1);
		}
		i++;
	}
	i--;
	while (i >= 0 && (str[i] == ' ' || str[i] == '\t'))
		i--;
	if (str[i] == '|')
	{
		write(2, "syntax err : | \n", 17);
		return (1);
	}
	return (0);
}
int	ms_prompt(t_env **env, int *exit_status)
{
	char	*cmd;
	char	**lexed;
	t_cmd	*cmd2;

	cmd = readline("$> ");
	add_history(cmd);
	if (cmd == NULL)
		return (2);
	if (is_tab(cmd) == 1 || ft_strlen(cmd) == 0)
		return (0);
	if (pre_syntax_check(cmd))
		return (0);
	lexed = ms_parse(cmd);
	if (check_errors(lexed) == 1)
		return (0);
	// printf("adsfadsf\n");.
	ms_rendercmd(lexed, *env, exit_status);
	// lexed = fix_args(lexed);
	cmd2 = ms_cmdgen(lexed);
	if (sear(&cmd2) == 1)
	{
		return (0);
	}
	// if (ma3rftch(&cmd2)==1)
	// 	return (0);
	exec_cmd(env, cmd2, exit_status);
	ms_errors(lexed);
	return (0);
}
void	sig(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		// rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	main(int argc, char **argv, char **envp)
{
	int					cmd_status;
	int					*exit_status;
	t_env				*env;
	struct sigaction	minisignols;

	(void)argv;
	(void)argc;
	exit_status = (int *)malloc(sizeof(int));
	minisignols.sa_handler = sig;
	sigemptyset(&minisignols.sa_mask);
	sigaddset(&minisignols.sa_mask, SIGQUIT);
	minisignols.sa_flags = 0;
	sigaction(SIGINT, &minisignols, NULL);
	sigaction(SIGQUIT, &minisignols, NULL);
	if (envp == NULL)
		return (EXIT_FAILURE);
	env = ms_env_new(envp);
	while (true)
	{
		cmd_status = ms_prompt(&env, exit_status);
		if (cmd_status != 0)
			return (cmd_status);
	}
}
/*expansion lakant wst double kyyakhhd akhir quote */