# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/08 12:57:30 by aelkheta          #+#    #+#              #
#    Updated: 2024/10/10 14:58:33 by aelkheta         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
GCCFLAGS = -Wall -Wextra -Werror
GEBUGFLAGS = -g3 -fsanitize=address
LIBFT = libraries/libft/libft.a
INCLUDES = -I includes
# MLXLFLAGS = -lmlx -lXext -lX11 -lm
MLXLFLAGS = ./libraries/minilibx-linux/libmlx_Linux.a -lXext -lX11 -lm
SRC_DIR = ./srcs
# MLXLFLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
NAME = cub3d
SRCS = $(SRC_DIR)/cub3d.c $(SRC_DIR)/images.c

OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Building..."
	@$(CC) $(GCCFLAGS) $(OBJS) $(MLXLFLAGS) $(GEBUGFLAGS) $(INCLUDES) $(LIBFT) -o $(NAME)
	@echo "Building done"

%.o: %.c
	@echo "Compiling object files..."
	@$(CC) $(GCCFLAGS) $(INCLUDES) $(GEBUGFLAGS) -c -o $@ $<
	@echo "Compiling object files done"

clean:
	@echo "Removing object files..."
	@rm -rf $(OBJS)
	@echo "Removing object files done"

fclean: clean
	@echo "Removing program name..."
	@rm -f $(NAME)
	@echo "Removing program name done"

re: fclean all

.PHONY: all clean fclean re
.SECONDARY: