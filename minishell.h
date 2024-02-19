/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhida <alakhida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 20:50:10 by alakhida          #+#    #+#             */
/*   Updated: 2024/02/18 23:02:37 by alakhida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>
#include <stdlib.h>
#include <stdbool.h>
#include "./libft/libft.h"

typedef struct    ms_cmd
{
    char **cmd;
	bool is_pipe;
    struct s_cmd *next;
}t_cmd;

#endif
