# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alakhida <alakhida@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/05 20:46:16 by alakhida          #+#    #+#              #
#    Updated: 2024/02/08 01:49:59 by alakhida         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	minishell

SRCS =	main.c\

OBJS = $(SRCS:.c=.o)

CC = gcc

CFLAGS += -Wall -Werror -Wextra -g3 -fsanitize=address

#CFLAGS += -g3 -fsanitize=address

RM = rm -rf

LIBFT = libft/libft.a
LIBFTDIR = libft
LIBFTLINK = -L $(LIBFTDIR) -lft


all:		$(NAME)

$(NAME):	complib echoCM $(OBJS) echoOK
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBFTLINK)

complib:
	$(MAKE) -C libft/

%.o:		%.c
	$(CC) -c $(CFLAGS) -o $@ $<
	printf "$(GREEN)██"

clean: echoCLEAN
	$(MAKE) -C $(LIBFTDIR) clean
	$(RM) $(OBJS)

fclean: clean echoFCLEAN
	$(MAKE) -C $(LIBFTDIR) fclean
	$(RM) $(OBJS)
	$(RM) $(NAME)

re:		fclean all

echoCM:
	echo "$(YELLOW)===> Compiling $(RED)Minishell$(END)\n"
echoOK:
	echo "$(GREEN) OK ===> Compilation Success$(END)\n"
echoCLEAN :
	echo "\n$(CYAN)===> Cleanning OBJS$(END)"
echoFCLEAN :
	echo "$(CYAN)===> Cleanning minishell & Libft$(END)\n"