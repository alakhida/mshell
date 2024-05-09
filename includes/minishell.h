#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
#include <fcntl.h>
# include <stdlib.h>
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
	char *file;
} t_red;

typedef struct ms_cmd
{
	t_red 			*red;
	// char 			**args;
	char			**cmd;
	e_type			input;
	char			*infile;
	e_type			output;
	char			*outfile;
	struct ms_cmd	*next;
}					t_cmd;

typedef struct t_env
{
	char			*varname;
	char			*value;
	struct t_env	*next;
}					t_env;

// function defs
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
int                 ft_strcmp(char *s1, char *s2);
int					ft_echo(t_cmd *cmnd);
void				exec_cmd(t_env **env, t_cmd *cmds);
int					exec_built_in(t_cmd *cmds, t_env **envp);
void				ft_env(t_env **env);
int					ft_unset(t_cmd *cmds, t_env **env);
void				ft_cd(t_cmd *cmds, t_env **env);
t_env				*add_node(char *var, char *value);
int					ft_pwd(t_cmd *cmds);
void				add_node_to_back(t_env **envp, t_env *node);
void				ft_export(t_cmd *cmds, t_env **envp);
int					ft_strchar(const char *s, int c);
void				ft_export_var(char *var, t_env **envp, t_env *current);
void				ft_env_export(t_env **env);
void	handle_pipe_chain(t_cmd *cmd, int pip[], int *save_stdout, bool pipe_chain);
void	handling_pipe(t_cmd *cmd, int pip[], int *save_stdout, bool pipe_chain);
void	exec_bin(t_cmd *cmd, char **envp, char *path, int *save_stdout, pid_t *child, bool pipe_chain);
void wait_child(pid_t *child);

#endif
