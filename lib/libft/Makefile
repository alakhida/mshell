# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alakhida <alakhida@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/15 06:43:19 by calmouht          #+#    #+#              #
#    Updated: 2024/05/15 07:32:48 by alakhida         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libft.a

SRCS =  ft_bzero.c ft_isalpha.c ft_isalnum.c \
		ft_isascii.c ft_isdigit.c ft_isprint.c \
		ft_memcpy.c ft_memmove.c ft_memset.c \
		ft_strlcpy.c ft_strlen.c ft_tolower.c \
		ft_toupper.c ft_atoi.c ft_strlcat.c \
		ft_memcpy.c ft_memcmp.c ft_memchr.c \
		ft_strnstr.c ft_strchr.c ft_strncmp.c \
		ft_calloc.c ft_strrchr.c ft_substr.c \
		ft_strtrim.c ft_strmapi.c ft_strjoin.c \
		ft_striteri.c ft_split.c ft_itoa.c \
		ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		ft_putstr_fd.c ft_strdup.c ft_strldup.c\

OBJECTS = ${SRCS:.c=.o}

HEADERS = /*.h

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	gcc -c $(FLAGS) $(SRCS) -I $(HEADERS)
	ar rc $(NAME) $(OBJECTS)
	ranlib $(NAME)

clean:
	rm -rf *.o

fclean:clean
	rm -f $(NAME)

re:fclean all