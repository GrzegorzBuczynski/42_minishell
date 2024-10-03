# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/28 11:57:40 by ssuchane          #+#    #+#              #
#    Updated: 2024/10/03 20:26:09 by ssuchane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS :=	ft_append_argv.c \
		ft_atoi.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_is_string_numeric.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_ispipe.c \
		ft_isprint.c \
		ft_isredirection.c \
		ft_iswhitespace.c \
		ft_itoa.c \
		ft_lstadd_back.c \
		ft_lstadd_front.c \
		ft_lstclear.c \
		ft_lstdelone.c \
		ft_lstiter.c \
		ft_lstlast.c \
		ft_lstmap.c \
		ft_lstnew.c \
		ft_lstsize.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_panic.c \
		ft_print_error.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c  \
		ft_putstr_fd.c \
		ft_skip_whitespace.c \
		ft_split.c \
		ft_strchr.c \
		ft_strcmp.c \
		ft_strcpy.c \
		ft_strdup.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strmapi.c \
		ft_strncmp.c \
		ft_strncpy.c \
		ft_strndup.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strtrim.c \
		ft_substr.c \
		ft_substr2.c \
		ft_toupper.c \
		ft_tolower.c \
		get_next_line.c	\

OBJS := $(SRCS:.c=.o)

NAME = libft.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror

.PHONY: all clean fclean re

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	rm -f $(OBJS) 

fclean: clean
	rm -f $(NAME)

re: fclean all