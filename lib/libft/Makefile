# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: calmouht <calmouht@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/06 19:40:42 by alakhida          #+#    #+#              #
#    Updated: 2024/03/08 07:23:12 by calmouht         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS=ft_memset.c ft_isalnum.c ft_isascii.c \
	ft_isprint.c ft_strlen.c ft_bzero.c \
	ft_isalpha.c ft_isdigit.c ft_memmove.c \
	ft_memcpy.c ft_strlcpy.c ft_tolower.c \
	ft_toupper.c ft_strlcat.c ft_strnstr.c \
	ft_strncmp.c ft_strchr.c ft_atoi.c \
	ft_strrchr.c ft_memchr.c ft_memcmp.c \
	ft_strdup.c ft_strnstr.c ft_calloc.c \
	ft_substr.c ft_strjoin.c ft_strtrim.c \
	ft_split.c ft_itoa.c ft_strmapi.c \
	ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
	ft_putendl_fd.c ft_putnbr_fd.c ft_strldup.c \

OBJECTS= ${SRCS:.c=.o}

HEADERS= libft.h

FLAGS = -Wall -Wextra -Werror

CC = gcc

all: $(NAME)

$(NAME):
	$(CC) -c $(FLAGS) $(SRCS)
	ar rcs $(NAME) $(OBJECTS)

clean:
	rm -f ${OBJECTS}

fclean:clean
	rm -f $(NAME)

re: fclean all
