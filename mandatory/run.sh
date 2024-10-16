# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    run.sh                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/16 14:59:40 by aelkheta          #+#    #+#              #
#    Updated: 2024/10/16 15:01:02 by aelkheta         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

gcc -Wall -Wextra -Werror -O3 -g3 -fsanitize=address srcs/frames.c -o raycasting_frames -lmlx -lXext -lX11 -lm
./raycasting_frames
rm -f ./raycasting_frames