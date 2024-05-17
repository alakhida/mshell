# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alakhida <alakhida@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/10 00:43:31 by calmouht          #+#    #+#              #
#    Updated: 2024/05/17 09:19:09 by alakhida         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS =  -I ~/homebrew/opt/readline/include #-g -fsanitize=address
RDLINE = -L ~/homebrew/opt/readline/lib
CC = gcc
NAME = minishell
LIBFT = lib/libft/libft.a
OBJ = build/main.o build/ms_parse.o build/ms_env.o build/ms_cmdgen.o build/ms_cmdrender.o build/ms_env_clone.o \
		build/ms_errors.o build/utility.o build/execution.o build/builtins.o build/ft_echo.o \
		build/ft_env.o build/ft_unset.o build/ft_cd.o build/exits.o build/redirections.o build/ft_pwd.o \
		build/ft_export.o build/ft_export2.o build/piping.o build/exec_red.o build/tools.o build/utility2.o \
		build/norm.o build/utility3.o build/utility4.o build/utility5.o build/arg_norm.o
INCLUDE = includes/minishell.h

build/%.o : src/%.c
	$(CC) $< $(CFLAGS) -c -o $@

all : build $(NAME)

build :
	mkdir build

$(LIBFT):
	$(MAKE) -C lib/libft

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(RDLINE) $(OBJ) $(LIBFT) -lreadline -o $(NAME)

clean:
	$(MAKE) fclean -C lib/libft; rm -rf build/

fclean : clean
	rm -rf $(NAME)

re : fclean all
