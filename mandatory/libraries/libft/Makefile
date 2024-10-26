# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/20 10:22:55 by aelkheta          #+#    #+#              #
#    Updated: 2024/10/26 14:15:06 by aelkheta         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fPIE 
AR = ar rc

SRCS_M = ft_atoi.c \
		ft_itoa.c \
		ft_putendl_fd.c \
		ft_strlcat.c \
		ft_substr.c \
		ft_bzero.c \
		ft_putnbr_fd.c \
		ft_strlcpy.c \
		ft_tolower.c \
		ft_calloc.c \
		ft_memchr.c \
		ft_putstr_fd.c \
		ft_strlen.c \
		ft_toupper.c \
		ft_isalnum.c \
		ft_memcmp.c \
		ft_split.c \
		ft_strmapi.c \
		ft_isalpha.c \
		ft_memcpy.c \
		ft_strchr.c \
		ft_strncmp.c \
		ft_strcmp.c \
		ft_isascii.c \
		ft_memmove.c \
		ft_strdup.c \
		ft_strnstr.c \
		ft_isdigit.c \
		ft_memset.c \
		ft_striteri.c \
		ft_strrchr.c \
		ft_isprint.c \
		ft_putchar_fd.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_free.c \
		get_next_line.c \
		ft_printf.c \
		ft_print_char.c \
		ft_print_hex_upp.c \
		ft_print_hex_low.c \
		ft_print_address.c \
		ft_putnbr_unsigned.c \
		ft_putnbr.c \
		ft_print_str.c \

OBJS_M = $(SRCS_M:.c=.o)

$(NAME): $(OBJS_M)
	$(AR) $(NAME) $(OBJS_M)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS_M) $(OBJS_B)

fclean: clean
	rm -f $(NAME)

re: fclean all 

.PHONY: all clean fclean