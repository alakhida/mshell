#include "../includes/minishell.h"

void		ft_env(t_env **env)
{
	t_env *curr;

	if (!env)
        return ;
	curr = *env;
	if (!curr)
		return ;
	while (curr != NULL)
	{
		if (curr->value != NULL)
			printf("%s=%s\n",curr->varname, curr->value);
		curr = curr->next;
	}
}