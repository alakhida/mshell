# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: calmouht <calmouht@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/10 00:43:31 by calmouht          #+#    #+#              #
#    Updated: 2024/05/17 05:38:51 by calmouht         ###   ########.fr        #
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
SRC = src/main.c src/ms_parse.c src/ms_env.c src/ms_cmdgen.c src/ms_cmdrender.c src/ms_env_clone.c \
		src/ms_errors.c src/utility.c src/execution.c src/builtins.c src/ft_echo.c \
		src/ft_env.c src/ft_unset.c src/ft_cd.c src/exits.c src/redirections.c src/ft_pwd.c \
		src/ft_export.c src/ft_export2.c src/piping.c src/exec_red.c src/tools.c src/utility2.c \
		src/norm.c src/utility3.c src/utility4.c src/utility5.c src/arg_norm.c
INCLUDE = includes/minishell.h

.SILENT:

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
