#!/bin/bash

gcc -Wall -Wextra -Werror -O3 -g3 -fsanitize=address dfs_visualized.c ../mandatory/libraries/minilibx-linux/libmlx_Linux.a -lXext -lX11 -lm && ./a.out && rm a.out