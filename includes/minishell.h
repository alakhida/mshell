/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhida <alakhida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 00:25:16 by calmouht          #+#    #+#             */
/*   Updated: 2024/05/12 05:18:45 by alakhida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

typedef enum
{
	NONE,
	HEREDOC, //<<
	LREDIR,  // <
	RREDIR,  // >
	APPEND,  // >>
	PIPE,    // |
}					e_type;

typedef struct t_red
{
	e_type type;
	char	*file;
	struct t_red *next;
} t_red;


typedef struct ms_cmd
{
	t_red			*red;
	char			**args;
	char			**cmd;
	char			*path;
	int				*std_out;
	char			**env;
	e_type			input;
	char			*infile;
	e_type			output;
	char			*outfile;
	int				count;
	struct ms_cmd	*next;
}					t_cmd;

typedef struct t_env
{
	char			*varname;
	char			*value;
	struct t_env	*next;
}					t_env;

typedef struct s_info
{
	char 	**envp;
	char	*path;	
	int		save_stdout;
	pid_t	child;
	bool	pipe_chain;
	int		saved_stdin;
	int		saved_stdout;
}	t_info;
// function defs
char				*val_malloc(char *cmd, char *var, int j);
char				*cpy_value(char *cmd, char *var, char *value, int j);
bool				pipe_chain_present(t_cmd *cmds);
void				export_to_list(t_env *current, char *var, char *value);
void				exits(int code);
void				get_redir(t_cmd **cmd);
char				**ms_parse(char *cmd);
t_env				*ms_env_new(char **envp);
int					ms_prompt(t_env **env);
t_cmd				*ms_cmdgen(char **cmd);
void				ms_rendercmd(char **command, t_env *head);
char				**ms_env_dup(t_env *env);
int					node_count(t_env *env);
t_env				*ms_env_search(char *ptr, t_env *head);
char				*expanded(char *cmd);
bool				ms_errors(char **cmd);
int					ms_count(char *s);
e_type				ms_ctrlop(char *str);
char				**ft_arrslice(char **arr, int start, int end);
char				*ft_strreplace(char *src, char *dst, char *replacement);
char				*ft_strreplace_all(char *src, char *dst, char *replacement);
int					ft_strcmp(char *s1, char *s2);
int					ft_echo(t_cmd *cmnd);
void				exec_cmd(t_env **env, t_cmd *cmds);
int					exec_built_in(t_cmd *cmds, t_env **envp);
void				ft_env(t_env **env);
int					ft_unset(t_cmd *cmds, t_env **env);
void				ft_cd(t_cmd *cmds, t_env **env);
t_env				*add_node(char *var, char *value);
void				printlist(t_cmd **head);
int					ft_pwd(t_cmd *cmds);
void				ft_export(t_cmd *cmds, t_env **envp);
int					ft_strchar(const char *s, int c);
void				ft_env_export(t_env **env);
void				add_node_to_back(t_env **envp, t_env *node);
void				exec_bin(t_cmd *cmd, t_info *info, t_env **env);
void				wait_child(pid_t *child);
void				handle_redirections(t_cmd *cmds);
char				*ft_strtok(char *str, const char *delim);
char				*ft_strcpy(char *dest, char *src);
char				*ft_strcat(char *dest, char *src);
void				exporting(t_cmd *cmds, t_env **envp);
bool				cmd_is_builtin(char *string);
void				handle_redirections(t_cmd *cmds);
char				*cmd_path(char *cmd, t_env *env);

#endif