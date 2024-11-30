# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/27 20:23:19 by aelkheta          #+#    #+#              #
#    Updated: 2024/11/29 09:32:28 by aelkheta         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := cc
GCCFLAGS := -Wall -Wextra -Werror
DEBUGFLAGS := -g3  -fsanitize=address
LIBFT := libraries/libft/libft.a
INCLUDES := -I includes
MAP ?= maps/map2.cub

MINILIBX_LINUX := ./libraries/minilibx-linux/libmlx_Linux.a
MINILIBX_MACOS := ./libraries/minilibx_opengl_20191021/libmlx.a

UNAME := $(shell uname)

ifeq ($(UNAME), Darwin)
    MLXLFLAGS := ${MINILIBX_MACOS} -framework OpenGL -framework AppKit
else
    MLXLFLAGS := ${MINILIBX_LINUX} -lXext -lX11 -lm
endif

NAME := cub3d_bonus

SRC_DIR := src
BUILD_DIR := build

SRCS := $(shell find $(SRC_DIR) -name '*.c')
OBJS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

all: $(NAME)

run: all
	@./$(NAME) ${MAP}
	@rm -f $(NAME)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(GCCFLAGS) ${DEBUGFLAGS} $(INCLUDES) -c $< -o $@

valg: all clean
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) ${MAP}
	@rm -f $(NAME)

$(NAME): $(OBJS)
	@echo "Building..."
	@$(CC) $(GCCFLAGS) ${DEBUGFLAGS} $(OBJS) $(MLXLFLAGS) $(INCLUDES) $(LIBFT) -o $(NAME)
	@echo "Building done"

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