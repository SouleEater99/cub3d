NAME = cub3d
RM = rm -rf
CC = cc  
CFLAG = -Wall -Wextra -Werror -fsanitize=address -g3
MLX_FLAG = -lX11 -lm -lz -lXext
LIBFT = include/lib_ft/libft.a
MLX_LIB =	./include/minilibx/minilibx-linux/libmlx.a \
			./include/minilibx/minilibx-linux/libmlx_Linux.a
SRC = ./src/cub3d.c\
		./src/init.c\
		./src/write_to_img.c\
		./src/ft_mlx_hook.c\
		./src/clean.c\
		./src/mlx_utils.c\
		./src/update_image.c\
		./src/ray_casting.c\
		./src/aziz_part/parsing.c

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAG) -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJ) $(MLX_LIB) $(LIBFT)
	$(CC) $(CFLAG) $(OBJ) $(LIBFT) $(MLX_LIB) $(MLX_FLAG) -o $(NAME)

$(LIBFT):
	@make -sC ./include/lib_ft all

$(MLX_LIB):
	@make -sC ./include/minilibx/minilibx-linux

clean :
	$(RM) $(OBJ)
	@make -sC ./include/lib_ft clean
	@make -sC ./include/minilibx/minilibx-linux clean

fclean : clean
	$(RM) $(NAME)
	@make -sC ./include/lib_ft fclean

re : fclean all