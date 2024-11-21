#include <mlx.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include "../libraries/libft/libft.h"
#include <fcntl.h>
#include <stdbool.h>
// #include "../includes/macros.h"

# define PI                 3.14159265358979323846

# define SCREEN_WIDTH       800
# define SCREEN_HEIGHT      600

# define RAY_LENGHT         500

# define MAP_WIDTH          30      // just an example
# define MAP_HEIGHT         9       // just an example

# define CLR_SKY            0x69c9fa
# define CLR_FLR            0xc28951

# define CLR_EAW            0xcacaca
# define CLR_SAN            0xf5f5f5

# define TILE_SIZE          64      // the cell grid size

# define CENTER             (SCREEN_WIDTH / 2 - MAP_WIDTH * TILE_SIZE / 2)

# define PLAYER_RADIUS      6
# define MINIMAP_RADIUS     80

# define SCALE              0.25

# define MAP_MID_X          (SCREEN_WIDTH / 2)
# define MAP_MID_Y          (SCREEN_HEIGHT / 2)

# define MINIMAP_MID_X      (SCREEN_WIDTH - MINIMAP_RADIUS - 20)
# define MINIMAP_MID_Y      (MINIMAP_RADIUS + 20)

# define LEFT_CLICK         1
# define MIDDLE_CLICK       2
# define RIGHT_CLICK        3
# define SCROLL_UP          4
# define SCROLL_DOWN        5

# ifdef __APPLE__
    // macOS keycodes
    # define ESC_KEY        53
    # define U_KEY          126
    # define D_KEY          125
    # define R_KEY          124
    # define L_KEY          123
    
    # define MOVE_SPEED     0.09     // player speed
    # define ROT_SPEED      0.06     // Rotation speed (in radians)

# elif __linux__
    // Linux (X11) keycodes
    # define ESC_KEY        65307
    # define U_KEY          65362
    # define D_KEY          65364
    # define R_KEY          65363
    # define L_KEY          65361
    
    # define MOVE_SPEED     0.006    // player speed
    # define ROT_SPEED      0.004    // Rotation speed (in radians)
# else
    #error "Unsupported platform"
# endif

typedef struct s_image
{
    void    *img_ptr;
    void    *img_data;
    int     bits_per_pixel;
    int     size_line;
    int     endian;
}   t_image;

typedef struct s_player
{
    double  dir_x;
    double  dir_y;
    double  player_x;
    double  player_y;
}   t_player;

typedef struct s_map
{
    char    **map;
    int     map_height;
    int     map_width;
    int     map_start;
}   t_map;

typedef struct s_structure
{
    char    *no_texture_path;
    char    *so_texture_path;
    char    *we_texture_path;
    char    *ea_texture_path;
}   t_texture;


typedef struct s_mlx
{
    void    *mlx_ptr;
    void    *win_ptr;
}    t_mlx;

typedef struct s_minimap
{
    double  scale;
    int     clicks;
    int     player_radius;
    int     minimap_radius;
    int     minimap_x_center;
    int     minimap_y_center;
}   t_minimap;

typedef struct s_data {

    t_mlx   mlx;
    t_map   map;

    double  dir_x;
    double  dir_y;
    double  camera_x;
    double  plane_x;
    double  plane_y;
    char    player_dir;
    double  player_x;
    double  player_y;

    int     map_x;
    int     map_y;

    double  ray_dir_x;
    double  ray_dir_y;

    double  side_dist_x;
    double  side_dist_y;
    double  delta_dist_x;
    double  delta_dist_y;

    int     step_x;
    int     step_y;
    
    short   rotate_right;
    short   rotate_left;
    short   move_forward;
    short   move_backward;
    
    int     hit;
    int     side;
    int     color;

    t_image *image;

    double  perp_wall_dist;
    int     line_height;
    int     draw_start;
    int     draw_end;

    t_texture   texture;

    double  rot_speed;
    double  move_speed;

    // int     floor_color;
    // int     ceiling_color;

    t_minimap   minimap;
} t_data;

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
    img->img_ptr = mlx_new_image(data->mlx.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!img->img_ptr)
    {
        free(img);
        return (NULL);
    }
    img->img_data = mlx_get_data_addr(img->img_ptr, &img->bits_per_pixel,
            &img->size_line, &img->endian);
    if (!img->img_data)
    {
        mlx_destroy_image(data->mlx.mlx_ptr, img->img_ptr);
        free(img);
        return (NULL);
    }
    return (img);
}

void free_map(char **map)
{
    int i;

    i = -1;
    if (!map)
        return;
    while (map[++i])
        free(map[i]);
    free(map);
}

int init_map(t_data *data)
{
    const char *map_lines[] = {
        "11111111111111111111111111111",
        "10000000000000000000000000001",
        "10001111111111000000000000001",
        "10000000000000001111111111101",
        "11000000000000000000000000001",
        "10000111111011111100000000001",
        "10000000000000000001111111101",
        "10000000000000000000000000001",
        "11111111111111111111111111111",
        NULL
    };

    data->map.map = (char **)malloc(sizeof(char *) * (data->map.map_height + 1));
    if (!data->map.map)
        return (1);

    for (int i = 0; map_lines[i]; i++)
    {
        data->map.map[i] = strdup(map_lines[i]);
        if (!data->map.map[i])
        {
            free_map(data->map.map);
            return (1);
        }
    }
    data->map.map[data->map.map_height] = NULL;
    return (0);
}

void init_player_direction(t_data *data)
{
    data->player_dir = 'S';  // Set default direction
    
    if (data->player_dir == 'N')
    {
        data->dir_x = 0;
        data->dir_y = -1;
        data->plane_x = 0.66;
        data->plane_y = 0;
    }
    else if (data->player_dir == 'S')
    {
        data->dir_x = 0;
        data->dir_y = 1;
        data->plane_x = -0.66;
        data->plane_y = 0;
    }
    else if (data->player_dir == 'W')
    {
        data->dir_x = -1;
        data->dir_y = 0;
        data->plane_x = 0;
        data->plane_y = 0.66;
    }
    else if (data->player_dir == 'E')
    {
        data->dir_x = 1;
        data->dir_y = 0;
        data->plane_x = 0;
        data->plane_y = -0.66;
    }
}

int init_game(t_data *data)
{
    data->rot_speed = ROT_SPEED;
    data->move_speed = MOVE_SPEED;
    data->minimap.scale = SCALE;
    data->minimap.player_radius = PLAYER_RADIUS;
    data->minimap.minimap_radius = MINIMAP_RADIUS;
    data->minimap.minimap_x_center = MINIMAP_MID_X;
    data->minimap.minimap_y_center = MINIMAP_MID_Y;

    data->map.map_width = MAP_WIDTH;
    data->map.map_height = MAP_HEIGHT;

    data->player_x = 2.0;
    data->player_y = 2.0;

    init_player_direction(data);

    if (init_map(data) != 0)
        return (1);

    // Create the persistent image
    data->image = create_image(data);
    if (!data->image)
        return (1);

    return (0);
}

void clean_up(t_data *data)
{
    if (!data)
        return;
        
    // if (data->texture.no_texture_path)
    //     free(data->texture.no_texture_path);
    // if (data->texture.so_texture_path)
    //     free(data->texture.so_texture_path);
    // if (data->texture.we_texture_path)
    //     free(data->texture.we_texture_path);
    // if (data->texture.ea_texture_path)
    //     free(data->texture.ea_texture_path);
    
    if (data->image)
    {
        if (data->image->img_ptr && data->mlx.mlx_ptr)
            mlx_destroy_image(data->mlx.mlx_ptr, data->image->img_ptr);
        free(data->image);
    }
    
    if (data->mlx.win_ptr && data->mlx.mlx_ptr)
        mlx_destroy_window(data->mlx.mlx_ptr, data->mlx.win_ptr);
    if (data->mlx.mlx_ptr)
    {
        mlx_destroy_display(data->mlx.mlx_ptr);
        free(data->mlx.mlx_ptr);
    }
    if (data->map.map)
        free_map(data->map.map);
}

int key_press(int keycode, t_data *data)
{
    if (keycode == ESC_KEY)
    {
        clean_up(data);
        exit(0);
    }
    else if (keycode == 'w' || keycode == U_KEY)
        data->move_forward = 1;
    else if (keycode == 's' || keycode == D_KEY)
        data->move_backward = 1;
    else if (keycode == 'a' || keycode == L_KEY)
        data->rotate_left = 1;
    else if (keycode == 'd' || keycode == R_KEY)
        data->rotate_right = 1;
    return (0);
}

int key_release(int keycode, t_data *data)
{
    if (keycode == 'w' || keycode == U_KEY)
        data->move_forward = 0;
    else if (keycode == 's' || keycode == D_KEY)
        data->move_backward = 0;
    else if (keycode == 'a' || keycode == L_KEY)
        data->rotate_left = 0;
    else if (keycode == 'd' || keycode == R_KEY)
        data->rotate_right = 0;
    return (0);
}

int check_click_space(t_data *data, int x, int y)
{
    int dx = x - data->minimap.minimap_x_center;
    int dy = y - data->minimap.minimap_y_center;
    double distance = sqrt(dx * dx + dy * dy);
    return (distance <= data->minimap.minimap_radius);
}

int mouse_events(int button, int x, int y, t_data *data)
{
    if (button == LEFT_CLICK && check_click_space(data, x, y))
    {
        data->minimap.clicks++;
        if (data->minimap.clicks % 2 != 0)
        {
            data->rot_speed = ROT_SPEED * 8;
            data->move_speed = MOVE_SPEED * 8;
            data->minimap.scale = SCALE * 2;
            data->minimap.player_radius = PLAYER_RADIUS;
            data->minimap.minimap_radius = MINIMAP_RADIUS * 10;
            data->minimap.minimap_x_center = MAP_MID_X;
            data->minimap.minimap_y_center = MAP_MID_Y;
        }
        else
        {
            data->rot_speed = ROT_SPEED;
            data->move_speed = MOVE_SPEED;
            data->minimap.scale = SCALE;
            data->minimap.player_radius = PLAYER_RADIUS;
            data->minimap.minimap_radius = MINIMAP_RADIUS;
            data->minimap.minimap_x_center = MINIMAP_MID_X;
            data->minimap.minimap_y_center = MINIMAP_MID_Y;
        }
    }
    return (0);
}

void draw_vert_line(t_image *image, int x, int draw_start, int draw_end, int color)
{
    int y;

    y = draw_start - 1;
    while (++y < draw_end)
        put_pixel_in_img(image, x, y, color);
}

void dda_algorithm(t_data *data)
{
    data->hit = 0;
    while (data->hit == 0)
    {
        if (data->side_dist_x < data->side_dist_y)
        {
            data->side_dist_x += data->delta_dist_x;
            data->map_x += data->step_x;
            data->side = 0;
        }
        else
        {
            data->side_dist_y += data->delta_dist_y;
            data->map_y += data->step_y;
            data->side = 1;
        }
        
        if (data->map_x < 0 || data->map_x >= data->map.map_width || 
            data->map_y < 0 || data->map_y >= data->map.map_height)
            break;
            
        if (data->map.map[data->map_y][data->map_x] == '1')
            data->hit = 1;
    }
}

void draw_vert_cols(t_data *data, int x)
{
    int color = 0xFFFFFF;

    if (data->side == 0)
        data->perp_wall_dist = data->side_dist_x - data->delta_dist_x;
    else
        data->perp_wall_dist = data->side_dist_y - data->delta_dist_y;

    color = (data->side == 0) ? CLR_EAW : CLR_SAN;

    data->line_height = (int)(SCREEN_HEIGHT / data->perp_wall_dist);
    data->draw_start = -data->line_height / 2 + SCREEN_HEIGHT / 2;
    data->draw_start = (data->draw_start < 0) ? 0 : data->draw_start;

    data->draw_end = data->line_height / 2 + SCREEN_HEIGHT / 2;
    data->draw_end = (data->draw_end >= SCREEN_HEIGHT) ? SCREEN_HEIGHT - 1 : data->draw_end;

    draw_vert_line(data->image, x, 0, data->draw_start, CLR_SKY);
    draw_vert_line(data->image, x, data->draw_start, data->draw_end, color);
    draw_vert_line(data->image, x, data->draw_end, SCREEN_HEIGHT, CLR_FLR);
}

void calculate_side_dist_x_y(t_data *data)
{
    if (data->ray_dir_x < 0)
    {
        data->step_x = -1;
        data->side_dist_x = (data->player_x - data->map_x) * data->delta_dist_x;
    }
    else
    {
        data->step_x = 1;
        data->side_dist_x = (data->map_x + 1.0 - data->player_x) * data->delta_dist_x;
    }
    
    if (data->ray_dir_y < 0)
    {
        data->step_y = -1;
        data->side_dist_y = (data->player_y - data->map_y) * data->delta_dist_y;
    }
    else
    {
        data->step_y = 1;
        data->side_dist_y = (data->map_y + 1.0 - data->player_y) * data->delta_dist_y;
    }
}

void raycasting(t_data *data)
{
    int x;
    
    x = -1;
    while (++x < SCREEN_WIDTH)
    {
        data->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
        data->ray_dir_x = data->dir_x + data->plane_x * data->camera_x;
        data->ray_dir_y = data->dir_y + data->plane_y * data->camera_x;

        // Calculate the current map square the ray is in
        data->map_x = (int)data->player_x;
        data->map_y = (int)data->player_y;

        // Calculate delta_dist based on ray direction
        data->delta_dist_x = fabs(1 / data->ray_dir_x);
        data->delta_dist_y = fabs(1 / data->ray_dir_y);

        // Calculate step and initial side_dist
        calculate_side_dist_x_y(data);

        // Perform DDA algorithm
        dda_algorithm(data);

        // Draw the vertical wall strips
        draw_vert_cols(data, x);
    }
}

void rotate_player(t_data *data, double rot_speed)
{
    double old_dir_x;
    double old_plane_x;

    old_dir_x = data->dir_x;
    old_plane_x = data->plane_x;
    
    data->dir_x = data->dir_x * cos(rot_speed) - data->dir_y * sin(rot_speed);
    data->dir_y = old_dir_x * sin(rot_speed) + data->dir_y * cos(rot_speed);
    data->plane_x = data->plane_x * cos(rot_speed) - data->plane_y * sin(rot_speed);
    data->plane_y = old_plane_x * sin(rot_speed) + data->plane_y * cos(rot_speed);
}

void move_player(t_data *data)
{
    if (data->move_forward)
    {
        if (data->map.map[(int)data->player_y]
            [(int)(data->player_x + data->dir_x * data->move_speed)] != '1')
            data->player_x += data->dir_x * data->move_speed;
        if (data->map.map[(int)(data->player_y + data->dir_y * data->move_speed)]
            [(int)data->player_x] != '1')
            data->player_y += data->dir_y * data->move_speed;
    }
    if (data->move_backward)
    {
        if (data->map.map[(int)data->player_y]
            [(int)(data->player_x - data->dir_x * data->move_speed)] != '1')
            data->player_x -= data->dir_x * data->move_speed;
        if (data->map.map[(int)(data->player_y - data->dir_y * data->move_speed)]
            [(int)data->player_x] != '1')
            data->player_y -= data->dir_y * data->move_speed;
    }
    if (data->rotate_right)
        rotate_player(data, data->rot_speed);
    if (data->rotate_left)
        rotate_player(data, -data->rot_speed);
}

void draw_background(t_data *data, t_image *image)
{
	for (int y = -data->minimap.minimap_radius; y <= data->minimap.minimap_radius; y++)
    {
        for (int x = -data->minimap.minimap_radius; x <= data->minimap.minimap_radius; x++)
        {
            double distance = sqrt(x * x + y * y);
            if (distance <= data->minimap.minimap_radius)
            {
                int screen_x = data->minimap.minimap_x_center + x;
                int screen_y = data->minimap.minimap_y_center + y;
                put_pixel_in_img(image, screen_x, screen_y, 0x222222);
            }
        }
    }
}

void draw_tile(t_data *data, t_image *image, double x, double y, int color)
{
    int     size;
    double  screen_x;
    double  screen_y;
    double  distance;

    size = (int)(TILE_SIZE * data->minimap.scale);
    screen_x = data->minimap.minimap_x_center + (x - data->player_x * TILE_SIZE * data->minimap.scale);
    screen_y = data->minimap.minimap_y_center + (y - data->player_y * TILE_SIZE * data->minimap.scale);
    
    int di = -1;
    while (++di < size)
    {
        int dj = -1;
        while (++dj < size)
        {
            distance = sqrt(pow(screen_x + di - data->minimap.minimap_x_center, 2)
                + pow(screen_y + dj - data->minimap.minimap_y_center, 2));
            if (distance <= data->minimap.minimap_radius)
                put_pixel_in_img(image, screen_x + di, screen_y + dj, color);
        }
    }
}

void draw_map(t_data *data, t_image *image)
{
    // double scale = 0.25;
    
    int visible_range = (int)(data->minimap.minimap_radius / (TILE_SIZE * data->minimap.scale)) + 1;
    
    int player_map_x = (int)data->player_x;
    int player_map_y = (int)data->player_y;
    
    for (int dy = -visible_range; dy <= visible_range; dy++)
    {
        for (int dx = -visible_range; dx <= visible_range; dx++)
        {
            int map_x = player_map_x + dx;
            int map_y = player_map_y + dy;
            
            // Check if the tile is within map bounds
            if (map_x >= 0 && map_x < MAP_WIDTH && map_y >= 0 && map_y < MAP_HEIGHT)
            {
                double tile_x = map_x * TILE_SIZE * data->minimap.scale;
                double tile_y = map_y * TILE_SIZE * data->minimap.scale;
                
                if (data->map.map[map_y][map_x] == '1')
                    draw_tile(data, image, tile_x, tile_y, 0x000000);
                else if (data->map.map[map_y][map_x] == '0')
                    draw_tile(data, image, tile_x, tile_y, 0xAAAAAA);
            }
        }
    }
}

void draw_player(t_data *data, t_image *image)
{
    int x;
    int y;
    double dist;

    x = -data->minimap.player_radius;
    while (++x <= data->minimap.player_radius)
    {
        y = -data->minimap.player_radius;
        while (++y <= data->minimap.player_radius)
        {
            dist = sqrt(x * x + y * y);
            if (dist <= data->minimap.player_radius)
                put_pixel_in_img(image, data->minimap.minimap_x_center + x,  data->minimap.minimap_y_center + y, 0xffff00);
        }
    }
}

void draw_player_direction(t_data *data, t_image *image)
{
    // Draw direction indicator
    double angle = atan2(data->dir_y, data->dir_x);
    double fov = 60 * PI / 180.0; // 60 degrees FOV
    int i = -30 - 1;
    while (++i <= 30)
    {
        double ray_angle = angle + (i * fov / 60);
        double ray_length = MINIMAP_RADIUS * 0.3; // Length of direction indicator
        
        double end_x = data->minimap.minimap_x_center + cos(ray_angle) * ray_length;
        double end_y = data->minimap.minimap_y_center + sin(ray_angle) * ray_length;
        
        // Draw ray line
        double dx = end_x - data->minimap.minimap_x_center;
        double dy = end_y - data->minimap.minimap_y_center;
        double steps = fmax(fabs(dx), fabs(dy));
        
        if (steps == 0)
			continue;
        
        double x_increment = dx / steps;
        double y_increment = dy / steps;
        double x = data->minimap.minimap_x_center;
        double y = data->minimap.minimap_y_center;
        
		int step = -1;
        while (++step <= steps)
        {
            double dist_x = x - data->minimap.minimap_x_center;
            double dist_y = y - data->minimap.minimap_y_center;
			
            if (sqrt(dist_x * dist_x + dist_y * dist_y) <= MINIMAP_RADIUS)
                put_pixel_in_img(image, round(x), round(y), 0xFF0000);
            x += x_increment;
            y += y_increment;
        }
    }
}

void draw_minimap(t_data *data)
{
    // draw black background for our minimap
	draw_background(data, data->image);
    
    // draw the map (floor and walls)
    draw_map(data, data->image);
    
    // Draw the player's vield od view
    draw_player_direction(data, data->image);
    
    // Draw the player dot (or just the player)	// TODO
    draw_player(data, data->image);
    
    // Draw the minimap border	// TODO
    // draw_minimap_border(data->image);
}

int game_loop(t_data *data)
{
    // Clear the image
    memset(data->image->img_data, 0, SCREEN_WIDTH * SCREEN_HEIGHT * (data->image->bits_per_pixel / 8));

    // Update player position based on movement
    move_player(data);

    // Perform raycasting
    raycasting(data);

    // Draw minimap
    draw_minimap(data);

    // Put image to window
    mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr, data->image->img_ptr, 0, 0);

    return (0);
}

int main(void)
{
    t_data data;

    memset(&data, 0, sizeof(t_data));
    data.mlx.mlx_ptr = mlx_init();
    if (!data.mlx.mlx_ptr)
        return (1);

    data.mlx.win_ptr = mlx_new_window(data.mlx.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT, "Raycaster");
    if (!data.mlx.win_ptr)
    {
        clean_up(&data);
        return (1);
    }

    if (init_game(&data) != 0)
    {
        clean_up(&data);
        return (1);
    }

    mlx_hook(data.mlx.win_ptr, 2, 1L<<0, key_press, &data);
    mlx_hook(data.mlx.win_ptr, 3, 1L<<1, key_release, &data);
    mlx_hook(data.mlx.win_ptr, 4, 1L<<2, mouse_events, &data);
    mlx_loop_hook(data.mlx.mlx_ptr, game_loop, &data);
    mlx_loop(data.mlx.mlx_ptr);

    return (0);
}