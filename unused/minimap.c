# include "../mandatory/libraries/minilibx-linux/mlx.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>

# define SCREEN_WIDTH       800
# define SCREEN_HEIGHT      600

# define MAP_H              10
# define MAP_W              18

# define TILE_SIZE          64
# define MOVE_SPEED         0.1

# define ESC_KEY            65307
# define UP_KEY             65362
# define DOWN_KEY           65364
# define RIGHT_KEY          65363
# define LEFT_KEY           65361

# define W_KEY              119
# define S_KEY              115
# define A_KEY              97
# define D_KEY              100

# define PI                 3.14159265358979323846

# define MINIMAP_RADIUS     80

typedef struct s_image
{
    void    *img_ptr;
    void    *img_data;
    int     bits_per_pixel;
    int     size_line;
    char    *addr;
    int     line_length;
    int     endian;
}           t_image;

typedef struct s_data
{
    void        *mlx_ptr;
    void        *wind_ptr;
    char        **map;
    double      player_x;
    double      player_y;
    t_image     *image;
    double      scale;
    int         minimap_radius;
    int         minimap_x_center;
    int         minimap_y_center;
    int         clicks;

    int         keys[65536];
}   t_data;

void    put_pixel_in_img(t_image *image, int x, int y, int color)
{
    int pixel_index;

    if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
        return;

    pixel_index = (y * image->size_line) + (x * (image->bits_per_pixel / 8));
    *(int *)(image->img_data + pixel_index) = color;
}

t_image *create_image(t_data *data)
{
    t_image *img;

    img = malloc(sizeof(t_image));
    if (!img)
        return (NULL);
    img->img_ptr = mlx_new_image(data->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!img->img_ptr)
    {
        free(img);
        return (NULL);
    }
    img->img_data = mlx_get_data_addr(img->img_ptr, &img->bits_per_pixel,
            &img->size_line, &img->endian);
    if (!img->img_data)
    {
        mlx_destroy_image(data->mlx_ptr, img->img_ptr);
        free(img);
        return (NULL);
    }
    return (img);
}

void free_map(char **map)
{
    int i;

    i = -1;
    while (map && map[++i])
        free(map[i]);
    free(map);
}

void clean_up(t_data *data)
{
    if (data->wind_ptr)
        mlx_destroy_window(data->mlx_ptr, data->wind_ptr);
    if (data->mlx_ptr)
    {
        mlx_destroy_display(data->mlx_ptr);
        free(data->mlx_ptr);
    }
    free_map(data->map);
}

int key_press(int keycode, t_data *data)
{
    if (keycode == ESC_KEY)
    {
        clean_up(data);
        exit(0);
    }
    if (keycode < 65536)
        data->keys[keycode] = 1;
    return (0);
}

int key_release(int keycode, t_data *data)
{
    if (keycode < 65536)
        data->keys[keycode] = 0;
    return (0);
}

char **init_map(t_data *data)
{
    char **map;

    map = malloc(sizeof(char *) * (MAP_H + 1));
    if (!map)
    {
        clean_up(data);
        exit(1);
    }

    map[0] = strdup("111111111111111111");
    map[1] = strdup("100000000000000001");
    map[2] = strdup("100000000000000001");
    map[3] = strdup("100000000000000001");
    map[4] = strdup("100000000000000001");
    map[5] = strdup("100000000000000001");
    map[6] = strdup("100000000000000001");
    map[7] = strdup("100000000000000001");
    map[8] = strdup("100000000000000001");
    map[9] = strdup("111111111111111111");
    map[10] = NULL;
    return (map);
}

void draw_background(t_data *data, t_image *image)
{
	for (int y = -data->minimap_radius; y <= data->minimap_radius; y++)
    {
        for (int x = -data->minimap_radius; x <= data->minimap_radius; x++)
        {
            double distance = sqrt(x * x + y * y);
            if (distance <= data->minimap_radius)
            {
                int screen_x = data->minimap_x_center + x;
                int screen_y = data->minimap_y_center + y;
                put_pixel_in_img(image, screen_x, screen_y, 0x222222);
            }
        }
    }
}

// void draw_tile(t_data *data, t_image *image, double x, double y, int color)
// {
//     int size = (int)(TILE_SIZE * data->scale);
//     // int i = x;
//     // int j;
    
//     // Calculate screen position relative to player's position
//     double screen_x =  + (x - data->player_x * TILE_SIZE * data->scale);
//     double screen_y = data->minimap_y_center + (y - data->player_y * TILE_SIZE * data->scale);
    
//     for (int di = 0; di < size; di++)
//     {
//         for (int dj = 0; dj < size; dj++)
//         {
//             double pixel_x = screen_x + di;
//             double pixel_y = screen_y + dj;
            
//             // Calculate distance from minimap center
//             double dx = pixel_x - data->minimap_x_center;
//             double dy = pixel_y - data->minimap_y_center;
//             double distance = sqrt(dx * dx + dy * dy);
            
//             // Only draw if inside the circle
//             if (distance <= data->minimap_radius)
//                 put_pixel_in_img(image, pixel_x, pixel_y, color);
//         }
//     }
// }

void draw_tile(t_data *data, t_image *image, double x, double y, int color)
{
    int     size;
    double  screen_x;
    double  screen_y;
    double  distance;

    size = (int)(TILE_SIZE * data->scale);
    screen_x = data->minimap_x_center + (x - data->player_x * TILE_SIZE * data->scale);
    screen_y = data->minimap_y_center + (y - data->player_y * TILE_SIZE * data->scale);
    
    int di = -1;
    while (++di < size)
    {
        int dj = -1;
        while (++dj < size)
        {
            distance = sqrt(pow(screen_x + di - data->minimap_x_center, 2)
                + pow(screen_y + dj - data->minimap_y_center, 2));
            if (distance <= data->minimap_radius)
                put_pixel_in_img(image, screen_x + di, screen_y + dj, color);
        }
    }
}

void draw_player(t_data *data, t_image *image)
{
    int x;
    int y;
    double dist;

    x = -3;
    while (++x <= 3)
    {
        y = -3;
        while (++y <= 3)
        {
            dist = sqrt(x * x + y * y);
            if (dist <= 3)
                put_pixel_in_img(image, data->minimap_x_center + x,  data->minimap_y_center + y, 0xFF0000);
        }
    }
}

void draw_map(t_data *data, t_image *image)
{
    // double scale = 0.25;
    
    int visible_range = (int)(data->minimap_radius / (TILE_SIZE * data->scale)) + 1;
    
    int player_map_x = (int)data->player_x;
    int player_map_y = (int)data->player_y;
    
    for (int dy = -visible_range; dy <= visible_range; dy++)
    {
        for (int dx = -visible_range; dx <= visible_range; dx++)
        {
            int map_x = player_map_x + dx;
            int map_y = player_map_y + dy;
            
            // Check if the tile is within map bounds
            if (map_x >= 0 && map_x < MAP_W && map_y >= 0 && map_y < MAP_H)
            {
                double tile_x = map_x * TILE_SIZE * data->scale;
                double tile_y = map_y * TILE_SIZE * data->scale;
                
                if (data->map[map_y][map_x] == '1')
                    draw_tile(data, image, tile_x, tile_y, 0x000000);
                else if (data->map[map_y][map_x] == '0')
                    draw_tile(data, image, tile_x, tile_y, 0xAAAAAA);
            }
        }
    }
}

void update_player(t_data *data)
{
    double new_x;
    double new_y;

    new_x = data->player_x;
    new_y = data->player_y;

    if (data->keys[W_KEY] || data->keys[UP_KEY])
        new_y -= MOVE_SPEED;
    if (data->keys[S_KEY] || data->keys[DOWN_KEY])
        new_y += MOVE_SPEED;
    if (data->keys[A_KEY] || data->keys[LEFT_KEY])
        new_x -= MOVE_SPEED;
    if (data->keys[D_KEY] || data->keys[RIGHT_KEY])
        new_x += MOVE_SPEED;

    // Collision detection
    if (data->map[(int)new_y][(int)new_x] != '1')
    {
        data->player_x = new_x;
        data->player_y = new_y;
    }
}

void draw_minimap(t_data *data)
{
    data->image = create_image(data);
    if (!data->image)
    {
        clean_up(data);
        exit(1);
    }
    
    draw_background(data, data->image);
    draw_map(data, data->image);
    draw_player(data, data->image);
    
    mlx_put_image_to_window(data->mlx_ptr, data->wind_ptr, data->image->img_ptr, 0, 0);
    mlx_destroy_image(data->mlx_ptr, data->image->img_ptr);
    free(data->image);
}

int game_loop(t_data *data)
{
    update_player(data);
    draw_minimap(data);
    return (0);
}

int mouse_events(int button, int x, int y, t_data *data)
{
	printf("Button %d pressed at (%d, %d)\n", button, y, x);
	if (button == 1)
    {
		data->clicks++;
        if (data->clicks % 2 != 0)
        {
            data->scale = 1;
            data->minimap_radius = 800;
        }
        else
        {
            data->scale = 0.25;
            data->minimap_radius = 80;
        }
        // printf("Left click!\n");

    }
	else if (button == 2)
		printf("Middle click!\n");
	else if (button == 3)
		printf("Right click!\n");
	else if (button == 4)
		printf("Scroll up!\n");
	else if (button == 5)
		printf("Scroll down!\n");
	return 0;
}

int main(void)
{
    t_data data;
    
    memset(&data, 0, sizeof(t_data));
    if (!(data.mlx_ptr = mlx_init()))
        return (1);

    if (!(data.wind_ptr = mlx_new_window(data.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT, "Minimap")))
    {
        mlx_destroy_display(data.mlx_ptr);
        free(data.mlx_ptr);
        return (1);
    }

    if (!(data.map = init_map(&data)))
        return (1);


    data.minimap_radius = MINIMAP_RADIUS;
    data.minimap_x_center =  SCREEN_WIDTH / 2;
    data.minimap_y_center =  SCREEN_HEIGHT / 2;
    data.scale = 0.25;
    data.player_x = 5.0;
    data.player_y = 5.0;

    mlx_hook(data.wind_ptr, 2, 1L << 0, key_press, &data);
    mlx_hook(data.wind_ptr, 3, 1L << 1, key_release, &data);
    mlx_mouse_hook(data.wind_ptr, mouse_events, &data);
    mlx_loop_hook(data.mlx_ptr, game_loop, &data);
    mlx_loop(data.mlx_ptr);
    return (0);
}
