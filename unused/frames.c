#include <math.h>
#include <mlx.h>
#include <stdio.h> // just for debugging
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define ESC_KEY 65307
#define U_KEY 65362
#define D_KEY 65364
#define R_KEY 65363
#define L_KEY 65361

#define RAY_LENGHT 500

#define TILE_SIZE 32 // the cell grid size

#define MAP_WIDTH 9  // just an example
#define MAP_HEIGHT 9 // just an example

// # define CLR_SKY        0x89CFF3
// # define CLR_FLR        0xB99470

// # define CLR_EAW        0xB5B5B5
// # define CLR_SAN        0xF5F5F5

#define CLR_SKY 0x69c9fa
#define CLR_FLR 0xc28951

#define CLR_EAW 0xcacaca
#define CLR_SAN 0xf5f5f5

#define MOVE_SPEED 0.009 // player speed per frame
#define ROT_SPEED 0.004  // rotation speed per frame (in radians)

typedef struct s_image
{
	void	*img_ptr;
	void	*img_data;
	int		bits_per_pixel;
	int		size_line;
	char	*addr;
	int		line_length;
	int		endian;
}			t_image;

typedef struct s_data
{
	char	**map;
	void	*mlx_ptr;
	void	*win_ptr;
	double dir_x; // player direction x position
	double dir_y; // player direction y position
	double	camera_x;
	double	plane_x;
	double	plane_y;
	double	player_x;
	double	player_y;
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	int		map_x;
	int		map_y;

	int		move_forward;
	int		move_backward;
	int		rotate_left;
	int		rotate_right;
	t_image	*image;
}			t_data;

void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	update_player(t_data *data)
{
	double	new_x;
	double	new_y;
	double	old_dir_x;
	double	old_plane_x;

	if (data->move_forward)
	{
		new_x = data->player_x + data->dir_x * MOVE_SPEED;
		new_y = data->player_y + data->dir_y * MOVE_SPEED;
		if (data->map[(int)new_y][(int)new_x] == '0')
		{
			data->player_x = new_x;
			data->player_y = new_y;
		}
	}
	if (data->move_backward)
	{
		new_x = data->player_x - data->dir_x * MOVE_SPEED;
		new_y = data->player_y - data->dir_y * MOVE_SPEED;
		if (data->map[(int)new_y][(int)new_x] == '0')
		{
			data->player_x = new_x;
			data->player_y = new_y;
		}
	}
	if (data->rotate_left)
	{
		old_dir_x = data->dir_x;
		data->dir_x = data->dir_x * cos(-ROT_SPEED) - data->dir_y
			* sin(-ROT_SPEED);
		data->dir_y = old_dir_x * sin(-ROT_SPEED) + data->dir_y
			* cos(-ROT_SPEED);
		old_plane_x = data->plane_x;
		data->plane_x = data->plane_x * cos(-ROT_SPEED) - data->plane_y
			* sin(-ROT_SPEED);
		data->plane_y = old_plane_x * sin(-ROT_SPEED) + data->plane_y
			* cos(-ROT_SPEED);
	}
	if (data->rotate_right)
	{
		old_dir_x = data->dir_x;
		data->dir_x = data->dir_x * cos(ROT_SPEED) - data->dir_y
			* sin(ROT_SPEED);
		data->dir_y = old_dir_x * sin(ROT_SPEED) + data->dir_y * cos(ROT_SPEED);
		old_plane_x = data->plane_x;
		data->plane_x = data->plane_x * cos(ROT_SPEED) - data->plane_y
			* sin(ROT_SPEED);
		data->plane_y = old_plane_x * sin(ROT_SPEED) + data->plane_y
			* cos(ROT_SPEED);
	}
}

/// @brief this function setting a pixel in an image with the cordinates given.
/// @param image t_image *image: A pointer to a struct that holds the image information. This struct typically includes:
/// @param img_data: A pointer to the raw image data (the actual pixel array).
/// @param size_line: The number of bytes that represent a single row (or "line") of pixels in the image.
/// @param bits_per_pixel: The number of bits used to represent a single pixel (often 32 bits, or 4 bytes).
/// @param endian: Information about the byte order (not used directly in this function).
/// @param x is the horizontal position of the coordinates of the pixel you want to modify.
/// @param y is the vertical position of the coordinates of the pixel you want to modify.
/// @param color The color value (in ARGB format) that will be applied to the specified pixel. This is typically a 32-bit integer where each byte represents a different color component (Alpha, Red, Green, Blue).
void	put_pixel_in_img(t_image *image, int x, int y, int color)
{
	int	pixel_index;

	pixel_index = (y * image->size_line) + (x * (image->bits_per_pixel / 8));
	*(int *)(image->img_data + pixel_index) = color;
}

/// @brief Create a new image.
/// @param data the struct that hold all what we need.
/// @return return an allocated pointer to the image created.
t_image	*create_image(t_data *data)
{
	t_image	*img;
	int		width;
	int		height;

	img = malloc(sizeof(t_image));
	width = SCREEN_WIDTH;
	height = SCREEN_HEIGHT;
	img->img_ptr = mlx_new_image(data->mlx_ptr, width, height);
	img->img_data = mlx_get_data_addr(img->img_ptr, &img->bits_per_pixel,
			&img->size_line, &img->endian);
	return (img);
}

void	draw_vert_line(t_image *image, int x, int draw_start, int draw_end,
		int color)
{
	int	y;

	y = draw_start - 1;
	while (++y < draw_end)
	{
		if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
			put_pixel_in_img(image, x, y, color);
	}
}

void	raycasting(t_data *data)
{
	int	x;
		double perp_wall_dist;
	int	hit;
		int side;
	int	color;
	int	line_height;
	int	draw_start;
	int	draw_end;

	data->image = create_image(data);
	x = -1;
	while (++x < SCREEN_WIDTH)
	{
		data->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
		// if x = 0 we'll get the leftmost ray direction and if x = SCREEN_WIDTH we'll get the rightmost ray direction.
		data->ray_dir_x = data->dir_x + data->plane_x * data->camera_x;
			// the direction of the ray.
		data->ray_dir_y = data->dir_y + data->plane_y * data->camera_x;
			// the direction of the ray.
		// the player postions tell us which cell we are in and where in this cell exactly.
		data->map_x = (int)data->player_x;
			// the x player position in the map grid that tell us which grid cell we are in.
		data->map_y = (int)data->player_y;
			// the y player position in the map grid that tell us which grid cell we are in.
		data->delta_dist_x = fabs(1 / data->ray_dir_x);
		data->delta_dist_y = fabs(1 / data->ray_dir_y);
		hit = 0;
		if (data->ray_dir_x < 0)
		{
			data->step_x = -1;
			data->side_dist_x = (data->player_x - data->map_x)
				* data->delta_dist_x;
		}
		else
		{
			data->step_x = 1;
			data->side_dist_x = (data->map_x + 1.0 - data->player_x)
				* data->delta_dist_x;
		}
		if (data->ray_dir_y < 0)
		{
			data->step_y = -1;
			data->side_dist_y = (data->player_y - data->map_y)
				* data->delta_dist_y;
		}
		else
		{
			data->step_y = 1;
			data->side_dist_y = (data->map_y + 1.0 - data->player_y)
				* data->delta_dist_y;
		}
		while (hit == 0)
		{
			if (data->side_dist_x < data->side_dist_y)
			{
				data->side_dist_x += data->delta_dist_x;
				data->map_x += data->step_x;
				side = 0;
			}
			else
			{
				data->side_dist_y += data->delta_dist_y;
				data->map_y += data->step_y;
				side = 1;
			}
			if (data->map_x < 0 || data->map_x >= MAP_WIDTH || data->map_y < 0
				|| data->map_y >= MAP_HEIGHT)
				break ; // we hit the border walls.
			if (data->map[data->map_y][data->map_x] == '1')
				hit = 1; // break ; we hit a wall;
		}
		if (side == 0)
			perp_wall_dist = data->side_dist_x - data->delta_dist_x;
		else
			perp_wall_dist = data->side_dist_y - data->delta_dist_y;
		color = 0xFFFFFF;
		if (side == 0)
		{
			color = CLR_EAW;
			// if (data->step_x > 0)        
				// this is mean the player look to the right or the East
			//     color = 0xFF0000;   // red color
			// else                   
				// this is mean the player look to the left or the West
			//     color = 0x00FF00;   // green color
		}
		else
		{
			color = CLR_SAN;
			// if (data->step_y > 0)        
				// this is mean the player look to the bottom or the South
			//     color = 0x0000FF;   // blue color
			// else                   
				// this is mean the player look to the top or the South
			//     color = 0xFFFF00;   // yellow color
		}
		line_height = (int)(SCREEN_HEIGHT / perp_wall_dist);
		draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
		if (draw_end >= SCREEN_HEIGHT)
			draw_end = SCREEN_HEIGHT - 1;
		draw_vert_line(data->image, x, 0, draw_start, CLR_SKY);
		draw_vert_line(data->image, x, draw_start, draw_end, color);
		draw_vert_line(data->image, x, draw_end, SCREEN_HEIGHT, CLR_FLR);
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->image->img_ptr,
		0, 0);
	mlx_destroy_image(data->mlx_ptr, data->image->img_ptr);
	free(data->image);
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == ESC_KEY)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		exit(0);
	}
	else if (keycode == U_KEY)
		data->move_forward = 1;
	else if (keycode == D_KEY)
		data->move_backward = 1;
	else if (keycode == L_KEY)
		data->rotate_left = 1;
	else if (keycode == R_KEY)
		data->rotate_right = 1;
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == U_KEY)
		data->move_forward = 0;
	else if (keycode == D_KEY)
		data->move_backward = 0;
	else if (keycode == L_KEY)
		data->rotate_left = 0;
	else if (keycode == R_KEY)
		data->rotate_right = 0;
	return (0);
}

int	game_loop(t_data *data)
{
	update_player(data);
	raycasting(data);
	return (0);
}

void	init_map(t_data *data)
{
	data->map = (char **)malloc(sizeof(char *) * (9 + 1));
	data->map[0] = strdup("11111111");
	data->map[1] = strdup("10000001");
	data->map[2] = strdup("10001111");
	data->map[3] = strdup("10000001");
	data->map[4] = strdup("11000001");
	data->map[5] = strdup("10000001");
	data->map[6] = strdup("10101001");
	data->map[7] = strdup("10001001");
	data->map[8] = strdup("11111111");
	data->map[9] = NULL;
}

void	init_game(t_data *data)
{
	data->dir_x = 1; // the player look to the East or the Right
	data->dir_y = 0; // the player look to the East or the Right
	data->plane_x = 0;    // for the field of view
	data->plane_y = 0.66; // for the field of view
	data->player_x = 2; // player positions
	data->player_y = 2; // player positions
	init_map(data);
}

int	main(void)
{
	t_data data;
	memset(&data, 0, sizeof(t_data));

	data.mlx_ptr = mlx_init();
	data.win_ptr = mlx_new_window(data.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT,
			"Raycaster");

	init_game(&data);

	mlx_hook(data.win_ptr, 2, 1L << 0, key_press, &data);
	mlx_hook(data.win_ptr, 3, 1L << 1, key_release, &data);
	mlx_loop_hook(data.mlx_ptr, game_loop, &data);

	mlx_loop(data.mlx_ptr);

	return (0);
}