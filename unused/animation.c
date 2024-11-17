/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 16:13:33 by aelkheta          #+#    #+#             */
/*   Updated: 2024/11/17 16:13:34 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// #include <time.h>

// void render_sprites(t_data *data)
// {
//     if (!data || !data->mlx_ptr || !data->win_ptr || !data->image)
//         return;

//     static int frame = 0;
//     static clock_t last_time = 0;
//     static int shoot = 0;

//     t_image *img = data->image;
//     t_image sprite_image = data->player.frames[0]; // Default sprite for rendering

//     if (data->shoot)
//     {
//         shoot = 1;
//         data->shoot = 0;
//     }

//     if (shoot)
//     {
//         // Animation speed (number of frames per second)
//         double animation_speed = 20.0; // Adjust as needed

//         clock_t current_time = clock();
//         double time_diff = (double)(current_time - last_time) / CLOCKS_PER_SEC;

//         if (time_diff >= 1.0 / animation_speed)
//         {
//             frame++;
//             last_time = current_time;
//         }

//         if (frame >= 22) // Reset animation
//         {
//             frame = 0;
//             shoot = 0;
//         }
//         else
//         {
//             sprite_image = data->player.frames[frame];
//         }
//     }

//     int x = SCREEN_WIDTH / 2 - sprite_image.width / 2;
//     int y = SCREEN_HEIGHT - sprite_image.height;

//     render_sprites_to_image(img, &sprite_image, x, y);
//     mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img->img_ptr, 0, 0);
// }
