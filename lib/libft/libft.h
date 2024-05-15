/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calmouht <calmouht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 22:47:29 by alakhida          #+#    #+#             */
/*   Updated: 2024/05/14 05:34:37 by calmouht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stddef.h>
# include <stdlib.h>

void			ft_putnbr_fd(int n, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putchar_fd(char c, int fd);
void			ft_striteri(char *s, void (*f) (unsigned int, char*));
char			*ft_strmapi(char const *s, char (*f) (unsigned int, char));
char			*ft_itoa(int n);
char			**ft_split(char const *s, char c);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_substr(char *s, unsigned int start, size_t len);
char			*ft_strdup(const char *s1);
void			ft_bzero(void *s, size_t n);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
char			*ft_strldup(char *s1, int len);
void			*ft_memset(void *b, int c, size_t len);
int				ft_strlen(char *s);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
size_t			ft_strlcpy(char *dst, char *src, size_t l);
int				ft_tolower(int c);
int				ft_toupper(int c);
char			*ft_strrchr(const char *s, int c);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_atoi(const char *str);
unsigned int	ft_strlcat(char *dst, const char *src, size_t dstsize);
char			*ft_strnstr(const char *h, const char *n, size_t l);
char			*ft_strchr(const char *s, int c);
int				ft_atoi(const char *str);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_calloc(size_t count, size_t size);

#endif
