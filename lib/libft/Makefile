# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alakhida <alakhida@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/15 06:43:19 by calmouht          #+#    #+#              #
#    Updated: 2024/05/17 09:15:56 by alakhida         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libft.a

OBJ =  ft_bzero.o ft_isalpha.o ft_isalnum.o \
		ft_isascii.o ft_isdigit.o ft_isprint.o \
		ft_memcpy.o ft_memmove.o ft_memset.o \
		ft_strlcpy.o ft_strlen.o ft_tolower.o \
		ft_toupper.o ft_atoi.o ft_strlcat.o \
		ft_memcpy.o ft_memcmp.o ft_memchr.o \
		ft_strnstr.o ft_strchr.o ft_strncmp.o \
		ft_calloc.o ft_strrchr.o ft_substr.o \
		ft_strtrim.o ft_strmapi.o ft_strjoin.o \
		ft_striteri.o ft_split.o ft_itoa.o \
		ft_putchar_fd.o ft_putendl_fd.o ft_putnbr_fd.o \
		ft_putstr_fd.o ft_strdup.o ft_strldup.o\

CC = cc

CFLAGS = -Wall -Wextra -Werror -std=c99

DEPS = libft.h

%.o: %.c $(DEPS)
	$(CC) -c $< $(CFLAGS)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all