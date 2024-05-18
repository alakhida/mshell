/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhida <alakhida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 00:25:16 by calmouht          #+#    #+#             */
/*   Updated: 2024/05/18 01:08:04 by alakhida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define SINGLE_Q 39
# define DOUBLE_Q 34
# define SYNT_ERR "minishell : syntax error near unexpected token `newline'\n"
# define NO_Q 0

# include "../lib/libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

typedef enum e_type
{
	NONE,
	HEREDOC,
	LREDIR,
	RREDIR,
	APPEND,
	PIPE,
}					t_type;

typedef struct t_red
{
	t_type			type;
	char			*file;
	struct t_red	*next;
}					t_red;

typedef struct ms_cmd
{
	t_red			*red;
	char			**args;
	char			**cmd;
	int				count;
	int				heredoc;
	struct ms_cmd	*next;
	int				flag;
}					t_cmd;

typedef struct t_env
{
	char			*varname;
	char			*value;
	struct t_env	*next;
}					t_env;

typedef struct s_info
{
	char			**envp;
	char			*path;
	int				save_stdout;
	pid_t			child;
	bool			pipe_chain;
	int				saved_stdin;
	int				saved_stdout;
	int				*ex_status;
}					t_info;

typedef struct s_norm
{
	int				i;
	int				j;
	char			*replacement;
	char			*var_name;
	char			*string;
	int				*ex_stts;
}					t_norm;

typedef struct s_expanded
{
	int				i;
	int				k;
	int				ex_len;
	char			*l7asol;
}					t_expanded;

int					g_signal_number;

int					pre_syntax_check(char *str);
char				*val_malloc(char *cmd, char *var, int j);
char				*cpy_value(char *cmd, char *var, char *value, int j);
bool				pipe_chain_present(t_cmd *cmds);
void				export_to_list(t_env *current, char *var, char *value);
void				exits(int code);
void				get_redir(t_cmd **cmd);
char				**ms_parse(char *cmd);
t_env				*ms_env_new(char **envp);
int					ms_prompt(t_env **env, int *exit_status);
t_cmd				*ms_cmdgen(char **cmd);
void				ms_rendercmd(char **command, t_env *head, int *exit_status,
						t_norm *index);
char				**ms_env_dup(t_env *env);
int					node_count(t_env *env);
t_env				*ms_env_search(char *ptr, t_env *head);
char				*expanded(char *cmd, int *exit_status);
bool				ms_errors(char **cmd);
t_type				ms_ctrlop(char *str);
char				**ft_arrslice(char **arr, int start, int end);
char				*ft_strreplace(char *src, char *dst, char *replacement);
char				*ft_strreplace_all(char *src, char *dst, char *replacement);
int					ft_strcmp(char *s1, char *s2);
int					ft_echo(t_cmd *cmnd);
void				exec_cmd(t_env **env, t_cmd *cmds, int *exit_status);
int					exec_built_in(t_cmd *cmds, t_env **envp);
int					ft_env(t_env **env);
int					ft_unset(t_cmd *cmds, t_env **env);
int					ft_cd(t_cmd *cmds, t_env **env);
t_env				*add_node(char *var, char *value);
int					ft_pwd(t_cmd *cmds);
int					ft_export(t_cmd *cmds, t_env **envp);
int					ft_strchar(const char *s, int c);
void				ft_env_export(t_env **env);
void				add_node_to_back(t_env **envp, t_env *node);
void				exec_bin(t_cmd *cmd, t_info *info, t_env **env);
void				wait_child(pid_t *child, t_info *info);
int					handle_redirections(t_cmd *cmds);
char				*ft_strtok(char *str, const char *delim);
char				*ft_strcpy(char *dest, char *src);
char				*ft_strcat(char *dest, char *src);
void				exporting(t_cmd *cmds, t_env **envp);
bool				cmd_is_builtin(char *string);
char				*cmd_path(char *cmd, t_env *env);
void				sig(int signal);
int					handle_here_doc(t_red *red);
int					is_special(char *tab);
int					check_errors(char **tab);
char				*ft_strstr(char *str, char *to_find);
void				free_dbl_ptr(char **ptr);
char				*copy_path(char *s1, char *s2);
char				*get_cmd_path(t_env *env);
void				update_exit(t_env **env, int exit);
int					handle_red_out(t_red *red);
int					handle_red_in(t_red *red);
void				free_all(t_cmd *cmd);
int					handle_red_append(t_red *red);
char				**fix_args(char **args);
void				remove_q(char *str);
int					count_var(char *str, char c);
int					is_token(char c);
int					t_strlen(char **str);
char				**tarray_copy(char **a);
void				arg_norm2(t_cmd *cmd);
bool				arg_norm_error(t_cmd *cmd, int i);
bool				arg_norm_error2(t_cmd *cmd, int i);
void				arg_norm_error3(t_cmd *cmd, int i);
void				add_node_back(t_red **red, t_red *new, char *file,
						t_type type);
void				ms_cmdgen_norm(char **cmd, t_cmd *current, int i,
						int checkpoint);
void				ms_cmdgen_norm2(char **cmd, t_cmd *current, int i);
void				update_exit(t_env **env, int exit);
bool				varname_ok(char *string, int j);

#endif