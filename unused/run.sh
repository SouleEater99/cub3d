# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    run.sh                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aziz <aziz@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/16 14:59:40 by aelkheta          #+#    #+#              #
#    Updated: 2024/10/25 21:49:06 by aziz             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

gcc -Wall -Wextra -Werror -O3 -g3 -fsanitize=address frames.c -o raycasting_frames ../mandatory/libraries/minilibx-linux/libmlx_Linux.a -lXext -lX11 -lm
./raycasting_frames
rm -f ./raycasting_frames