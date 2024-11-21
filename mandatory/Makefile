# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/08 12:57:30 by aelkheta          #+#    #+#              #
#    Updated: 2024/11/21 09:59:33 by aelkheta         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := cc
GCCFLAGS := -Wall -Wextra -Werror
DEBUGFLAGS := -g3 -fsanitize=address
LIBFT := libraries/libft/libft.a
INCLUDES := -I includes
# MAP := maps/valid_map1.cub

MAP ?= maps/invalid_map2.cub

# MLXLFLAGS = -lmlx -lXext -lX11 -lm

# OS detection
UNAME := $(shell uname)

ifeq ($(UNAME),Darwin)
    # macOS flags
    MLXLFLAGS := ./libraries/minilibx_opengl_20191021/libmlx.a -framework OpenGL -framework AppKit
else
    # Linux flags
    MLXLFLAGS := ./libraries/minilibx-linux/libmlx_Linux.a -lXext -lX11 -lm
endif

SRC_DIR := ./srcs
NAME := cub3d
SRCS := $(SRC_DIR)/cub3d.c $(SRC_DIR)/images.c $(SRC_DIR)/raycasting.c $(SRC_DIR)/init_utiles.c $(SRC_DIR)/key_events.c $(SRC_DIR)/release_res.c $(SRC_DIR)/parsing.c $(SRC_DIR)/errors.c $(SRC_DIR)/minimap.c $(SRC_DIR)/animation.c $(SRC_DIR)/mouse_hook.c
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

# ====================================== #

# CC := cc
# GCCFLAGS := -Wall -Wextra -Werror
# DEBUGFLAGS := -g3 # -fsanitize=address
# LIBFT := libraries/libft/libft.a
# INCLUDES := -I includes
# MAP ?= maps/valid_map1.cub

# # OS detection
# UNAME := $(shell uname)

# ifeq ($(UNAME),Darwin)
#     # macOS flags
#     MLXLFLAGS := ./libraries/minilibx_opengl_20191021/libmlx.a -framework OpenGL -framework AppKit
# else
#     # Linux flags
#     MLXLFLAGS := ./libraries/minilibx-linux/libmlx_Linux.a -lXext -lX11 -lm
# endif

# SRC_DIR := ./srcs
# NAME := cub3d
# SRCS := $(SRC_DIR)/cub3d.c $(SRC_DIR)/images.c $(SRC_DIR)/raycasting.c $(SRC_DIR)/init_utiles.c $(SRC_DIR)/key_events.c $(SRC_DIR)/release_res.c $(SRC_DIR)/parsing.c $(SRC_DIR)/errors.c $(SRC_DIR)/minimap.c
# OBJS := $(SRCS:%.c=%.o)

# TOTAL_FILES := $(words $(SRCS))
# COMPILED_FILES = 0

# # Function to increment the compiled file count and display progress inline
# define count_progress
#     $(eval COMPILED_FILES=$(shell echo $$(( $(COMPILED_FILES) + 1 ))))
#     @echo -ne "\r[ $$(( $(COMPILED_FILES) * 100 / $(TOTAL_FILES) ))% ] Compiling $<"
# endef

# all: $(NAME)

# run: all clean
# 	@./$(NAME) ${MAP}
# 	@rm -f $(NAME)

# valg: all clean
# 	@valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) ${MAP}
# 	@rm -f $(NAME)

# $(NAME): $(OBJS)
# 	@$(CC) $(GCCFLAGS) $(OBJS) $(MLXLFLAGS) $(DEBUGFLAGS) $(INCLUDES) $(LIBFT) -o $(NAME)

# %.o: %.c
# 	@$(call count_progress)
# 	@$(CC) $(GCCFLAGS) $(INCLUDES) $(DEBUGFLAGS) -c -o $@ $<

# clean:
# 	@rm -rf $(OBJS)

# fclean: clean
# 	@rm -f $(NAME)

# re: fclean all

# .PHONY: all clean fclean re
# .SECONDARY:

# ====================================== #

# CC := cc
# GCCFLAGS := -Wall -Wextra -Werror
# DEBUGFLAGS := -g3 # -fsanitize=address
# LIBFT := libraries/libft/libft.a
# INCLUDES := -I includes
# MAP ?= maps/valid_map1.cub

# # OS detection
# UNAME := $(shell uname)

# ifeq ($(UNAME),Darwin)
#     # macOS flags
#     MLXLFLAGS := ./libraries/minilibx_opengl_20191021/libmlx.a -framework OpenGL -framework AppKit
# else
#     # Linux flags
#     MLXLFLAGS := ./libraries/minilibx-linux/libmlx_Linux.a -lXext -lX11 -lm
# endif

# SRC_DIR := ./srcs
# NAME := cub3d
# SRCS := $(SRC_DIR)/cub3d.c $(SRC_DIR)/images.c $(SRC_DIR)/raycasting.c $(SRC_DIR)/init_utiles.c $(SRC_DIR)/key_events.c $(SRC_DIR)/release_res.c $(SRC_DIR)/parsing.c $(SRC_DIR)/errors.c $(SRC_DIR)/minimap.c
# OBJS := $(SRCS:%.c=%.o)

# TOTAL_FILES := $(words $(SRCS))
# COMPILED_FILES = 0

# # Function to increment the compiled file count and display progress inline
# define count_progress
#     $(eval COMPILED_FILES=$(shell echo $$(( $(COMPILED_FILES) + 1 ))))
#     @echo -ne "\r[ $$(( $(COMPILED_FILES) * 100 / $(TOTAL_FILES) ))% ] Compiling..."
# endef

# all: $(NAME)

# run: all clean
# 	@./$(NAME) ${MAP}
# 	@rm -f $(NAME)

# valg: all clean
# 	@valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) ${MAP}
# 	@rm -f $(NAME)

# $(NAME): $(OBJS)
# 	@echo -ne "\rLinking..."
# 	@$(CC) $(GCCFLAGS) $(OBJS) $(MLXLFLAGS) $(DEBUGFLAGS) $(INCLUDES) $(LIBFT) -o $(NAME)
# 	@echo -e "\r[ 100% ] Build completed."

# %.o: %.c
# 	@$(call count_progress)
# 	@$(CC) $(GCCFLAGS) $(INCLUDES) $(DEBUGFLAGS) -c -o $@ $<

# clean:
# 	@rm -rf $(OBJS)
# 	@echo "Cleaned up object files."

# fclean: clean
# 	@rm -f $(NAME)
# 	@echo "Removed executable."

# re: fclean all

# .PHONY: all clean fclean re
# .SECONDARY:

# ====================================== #

# CC := cc
# GCCFLAGS := -Wall -Wextra -Werror
# DEBUGFLAGS := -g3 #-fsanitize=address
# LIBFT := libraries/libft/libft.a
# INCLUDES := -I includes
# MAP ?= maps/valid_map1.cub

# # OS detection
# UNAME := $(shell uname)
# ifeq ($(UNAME),Darwin)
#     # macOS flags
#     MLXLFLAGS := ./libraries/minilibx_opengl_20191021/libmlx.a -framework OpenGL -framework AppKit
# else
#     # Linux flags
#     MLXLFLAGS := ./libraries/minilibx-linux/libmlx_Linux.a -lXext -lX11 -lm
# endif

# SRC_DIR := ./srcs
# NAME := cub3d
# SRCS := $(SRC_DIR)/cub3d.c $(SRC_DIR)/images.c $(SRC_DIR)/raycasting.c $(SRC_DIR)/init_utiles.c $(SRC_DIR)/key_events.c $(SRC_DIR)/release_res.c $(SRC_DIR)/parsing.c $(SRC_DIR)/errors.c $(SRC_DIR)/minimap.c
# OBJS := $(SRCS:%.c=%.o)
# TOTAL_FILES := $(words $(SRCS))
# CURRENT_FILE = 0

# define progress
#     printf "\033[2K\r[ %3d%% ] Compiling..." "$$(($(CURRENT_FILE) * 100 / $(TOTAL_FILES)))"
# endef

# all: $(NAME)

# run: all clean
# 	@./$(NAME) ${MAP}
# 	@rm -f $(NAME)

# valg: all clean
# 	@valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) ${MAP}
# 	@rm -f $(NAME)

# $(NAME): $(OBJS)
# 	@printf "\033[2K\r[ 95%% ] Linking..."
# 	@$(CC) $(GCCFLAGS) $(OBJS) $(MLXLFLAGS) $(DEBUGFLAGS) $(INCLUDES) $(LIBFT) -o $(NAME)
# 	@printf "\033[2K\r[ 100%% ] Build completed.\n"

# %.o: %.c
# 	@$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE) + 1))))
# 	@$(call progress)
# 	@$(CC) $(GCCFLAGS) $(INCLUDES) $(DEBUGFLAGS) -c -o $@ $<

# clean:
# 	@rm -rf $(OBJS)
# 	@echo "Cleaned up object files."

# fclean: clean
# 	@rm -f $(NAME)
# 	@echo "Removed executable."

# re: fclean all

# .PHONY: all clean fclean re
# .SECONDARY: