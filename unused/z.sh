#!/bin/bash

if [ $# -ne 1 ];then
	echo "bad arguments: <./pp> <map_path>"
	exit 1
fi

gcc -Wall -Wextra -Werror -O3 -g3 -fsanitize=address ./srcs/pp.c -o pp ./libraries/minilibx-linux/libmlx_Linux.a ./libraries/libft/libft.a -lXext -lX11 -lm

./pp $1
rm pp
