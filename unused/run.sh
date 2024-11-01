# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    run.sh                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aziz <aziz@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/16 14:59:40 by aelkheta          #+#    #+#              #
#    Updated: 2024/10/26 21:52:12 by aziz             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


#!/bin/bash

gcc -Wall -Wextra -Werror -O3 -g3 frames.c -o raycasting_frames ../mandatory/libraries/minilibx-linux/libmlx_Linux.a -lXext -lX11 -lm
# gcc -Wall -Wextra -Werror -O3 -g3 frames.c -o raycasting_frames -lmlx -lXext -lX11 -lm # -fsanitize=address
./raycasting_frames
rm -f ./raycasting_frames