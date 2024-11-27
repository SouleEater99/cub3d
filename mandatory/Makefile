# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/27 20:23:19 by aelkheta          #+#    #+#              #
#    Updated: 2024/11/27 20:26:52 by aelkheta         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := cc
GCCFLAGS := -Wall -Wextra -Werror
DEBUGFLAGS := -g3 -fsanitize=address
LIBFT := libraries/libft/libft.a
INCLUDES := -I includes
MAP ?= maps/invalid_map2.cub

# MLXLFLAGS = -lmlx -lXext -lX11 -lm
MINILIBX_LINUX := ./libraries/minilibx-linux/libmlx_Linux.a
MINILIBX_MACOS := ./libraries/minilibx_opengl_20191021/libmlx.a
# OS detection
UNAME := $(shell uname)

ifeq ($(UNAME),Darwin)
    # macOS flags
    MLXLFLAGS := ${MINILIBX_MACOS} -framework OpenGL -framework AppKit
else
    # Linux flags
    MLXLFLAGS := ${MINILIBX_LINUX} -lXext -lX11 -lm
endif

# SRC_DIR := ./src
NAME := cub3d
SRCS = ./src/abdelali/cub3d.c\
		./src/abdelali/init.c\
		./src/abdelali/write_to_img.c\
		./src/abdelali/ft_mlx_hook.c\
		./src/abdelali/clean.c\
		./src/abdelali/mlx_utils.c\
		./src/abdelali/update_image.c\
		./src/abdelali/ray_casting.c\
		./src/aziz/parsing.c\
		./src/aziz/minimap.c\
		./src/aziz/shadow.c\
		./src/aziz/animation.c\
		./src/aziz/mouse_events.c\

OBJS := $(SRCS:%.c=%.o)

all: $(NAME)
	# make -C ./libraries/libft
	# make clean -C ./libraries/libft

run: all
	@./$(NAME) ${MAP}
	@rm -f $(NAME)

valg: all clean
	@valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) ${MAP}
	@rm -f $(NAME)

proj:
	@gcc -Wall -Wextra -Werror -O3 -g3 -fsanitize=address ./srcs/project.c -o raycasting ./libraries/minilibx-linux/libmlx_Linux.a ./libraries/libft/libft.a -lXext -lX11 -lm
	@./raycasting ${MAP} && rm ./raycasting

$(NAME): $(OBJS)
	@echo "Building..."
	@$(CC) $(GCCFLAGS) ${DEBUGFLAGS} $(OBJS) $(MLXLFLAGS) $(INCLUDES) $(LIBFT) -o $(NAME)
	@echo "Building done"

%.o: %.c
	@echo "Compiling object files..."
	@$(CC) $(GCCFLAGS) ${DEBUGFLAGS} $(INCLUDES) -c -o $@ $<
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

# CC = cc  

# NAME = cub3d

# MAP ?= ./maps/map1.cub

# RM = rm -rf

# CFLAG = -Wall -Wextra -Werror -fsanitize=address -g3

# MLX_FLAG = -lX11 -lm -lz -lXext

# LIBFT = include/libft/libft.a

# MLX_LIB =	./include/minilibx/minilibx-linux/libmlx.a \
# 			./include/minilibx/minilibx-linux/libmlx_Linux.a
# SRC = ./src/abdelali/cub3d.c\
# 		./src/abdelali/init.c\
# 		./src/abdelali/write_to_img.c\
# 		./src/abdelali/ft_mlx_hook.c\
# 		./src/abdelali/clean.c\
# 		./src/abdelali/mlx_utils.c\
# 		./src/abdelali/update_image.c\
# 		./src/abdelali/ray_casting.c\
# 		./src/aziz/parsing.c\
# 		./src/aziz/minimap.c\
# 		./src/aziz/shadow.c\
# 		./src/aziz/animation.c\
# 		./src/aziz/mouse_events.c\

# OBJ = $(SRC:.c=.o)

# %.o: %.c
# 	$(CC) $(CFLAG) -c $< -o $@

# all : $(NAME) clean

# run: all
# 	./cub3d $(MAP)

# $(NAME) : $(OBJ) #  $(MLX_LIB) $(LIBFT)
# 	$(CC) $(CFLAG) $(OBJ) $(LIBFT) $(MLX_LIB) $(MLX_FLAG) -o $(NAME)

# $(LIBFT):
# 	@make -sC ./include/libft all

# $(MLX_LIB):
# 	@make -sC ./include/minilibx/minilibx-linux

# clean :
# 	$(RM) $(OBJ)
# 	# @make -sC ./include/libft clean
# 	# @make -sC ./include/minilibx/minilibx-linux clean

# fclean : clean
# 	$(RM) $(NAME)
# 	# @make -sC ./include/libft fclean

# re : fclean all clean