# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alakhida <alakhida@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/05 20:46:16 by alakhida          #+#    #+#              #
#    Updated: 2024/02/05 20:49:06 by alakhida         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = main.c

OBJ = $(SRC:.c=.o)

CC = cc
#-Wall -Wextra -Werror
CFLAGS = #-g -fsanitize=address

LIBFT = ./libft/libft.a

RM = rm -f

all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

$(NAME): $(OBJ)
		make -C ./libft
		$(CC) $(CFLAFS) -o $(NAME) $(OBJ) $(LIBFT)

clean:
	make clean -C ./libft
	$(RM) $(OBJ)

fclean:clean
	make fclean -C ./libft
	$(RM) $(NAME)

re: fclean all
