// Add this to your t_data struct:
typedef struct s_data
{
    // ... existing members ...
    int is_minimap_fullscreen;  // New member to track minimap state
} t_data;

// Modify the mouse_events function:
int mouse_events(int button, int x, int y, t_data *data)
{
    (void)x;
    (void)y;
    
    if (button == 3) // Right click
    {
        data->is_minimap_fullscreen = !data->is_minimap_fullscreen;
        return (1);
    }
    return (0);
}

// Modify the draw_tile function to handle both modes:
void draw_tile(t_image *image, double x, double y, int color, t_data *data, double scale)
{
    int size = (int)(TILE_SIZE * scale);
    double screen_x, screen_y;
    
    if (data->is_minimap_fullscreen)
    {
        // Center the map on screen when fullscreen
        screen_x = (SCREEN_WIDTH / 2) + (x - data->player_x * TILE_SIZE * scale);
        screen_y = (SCREEN_HEIGHT / 2) + (y - data->player_y * TILE_SIZE * scale);
        
        // Draw if within screen bounds
        if (screen_x >= 0 && screen_x < SCREEN_WIDTH && screen_y >= 0 && screen_y < SCREEN_HEIGHT)
        {
            for (int di = 0; di < size; di++)
            {
                for (int dj = 0; dj < size; dj++)
                {
                    if (screen_x + di < SCREEN_WIDTH && screen_y + dj < SCREEN_HEIGHT)
                        put_pixel_in_img(image, screen_x + di, screen_y + dj, color);
                }
            }
        }
    }
    else
    {
        // Original minimap drawing logic
        screen_x = MINIMAP_CENTER_X + (x - data->player_x * TILE_SIZE * scale);
        screen_y = MINIMAP_CENTER_Y + (y - data->player_y * TILE_SIZE * scale);
        
        for (int di = 0; di < size; di++)
        {
            for (int dj = 0; dj < size; dj++)
            {
                double pixel_x = screen_x + di;
                double pixel_y = screen_y + dj;
                
                double dx = pixel_x - MINIMAP_CENTER_X;
                double dy = pixel_y - MINIMAP_CENTER_Y;
                double distance = sqrt(dx * dx + dy * dy);
                
                if (distance <= MINIMAP_RADIUS)
                    put_pixel_in_img(image, pixel_x, pixel_y, color);
            }
        }
    }
}

// Modify the draw_player_direction function:
void draw_player_direction(t_data *data, t_image *image)
{
    double center_x = data->is_minimap_fullscreen ? SCREEN_WIDTH / 2 : MINIMAP_CENTER_X;
    double center_y = data->is_minimap_fullscreen ? SCREEN_HEIGHT / 2 : MINIMAP_CENTER_Y;
    double ray_length = data->is_minimap_fullscreen ? SCREEN_HEIGHT * 0.3 : MINIMAP_RADIUS * 0.3;
    
    double angle = atan2(data->dir_y, data->dir_x);
    double fov = 60 * PI / 180.0;
    
    for (int i = -30; i <= 30; i += 2)
    {
        double ray_angle = angle + (i * fov / 60);
        double end_x = center_x + cos(ray_angle) * ray_length;
        double end_y = center_y + sin(ray_angle) * ray_length;
        
        double dx = end_x - center_x;
        double dy = end_y - center_y;
        double steps = fmax(fabs(dx), fabs(dy));
        
        if (steps == 0) continue;
        
        double x_increment = dx / steps;
        double y_increment = dy / steps;
        double x = center_x;
        double y = center_y;
        
        for (int step = 0; step <= steps; step++)
        {
            if (data->is_minimap_fullscreen)
            {
                if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
                    put_pixel_in_img(image, round(x), round(y), 0xFF0000);
            }
            else
            {
                double dist_x = x - center_x;
                double dist_y = y - center_y;
                if (sqrt(dist_x * dist_x + dist_y * dist_y) <= MINIMAP_RADIUS)
                    put_pixel_in_img(image, round(x), round(y), 0xFF0000);
            }
            x += x_increment;
            y += y_increment;
        }
    }
}

// Modify the draw_player function:
void draw_player(t_image *image, t_data *data)
{
    double center_x = data->is_minimap_fullscreen ? SCREEN_WIDTH / 2 : MINIMAP_CENTER_X;
    double center_y = data->is_minimap_fullscreen ? SCREEN_HEIGHT / 2 : MINIMAP_CENTER_Y;
    int player_size = data->is_minimap_fullscreen ? 6 : 3;
    
    for (int dy = -player_size; dy <= player_size; dy++)
    {
        for (int dx = -player_size; dx <= player_size; dx++)
        {
            if (dx * dx + dy * dy <= player_size * player_size)
            {
                double x = center_x + dx;
                double y = center_y + dy;
                
                if (data->is_minimap_fullscreen)
                {
                    if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
                        put_pixel_in_img(image, x, y, 0xFF0000);
                }
                else if (sqrt(dx * dx + dy * dy) <= MINIMAP_RADIUS)
                {
                    put_pixel_in_img(image, x, y, 0xFF0000);
                }
            }
        }
    }
}

// Modify the draw_mini_map function:
void draw_mini_map(t_data *data)
{
    // Calculate appropriate scale based on mode
    double scale = data->is_minimap_fullscreen ? 1.0 : 0.5;
    
    // Draw the map
    draw_map(data, data->image);
    
    // Draw the player's view cone
    draw_player_direction(data, data->image);
    
    // Draw the player dot
    draw_player(data->image, data);
    
    // Only draw border for mini mode
    if (!data->is_minimap_fullscreen)
        draw_minimap_border(data->image);
}

// Modify start_game function:
void start_game(t_data *data)
{
    data->image = create_image(data);

    if (!data->is_minimap_fullscreen)
        raycasting(data);
    draw_mini_map(data);

    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->image->img_ptr, 0, 0);
    mlx_destroy_image(data->mlx_ptr, data->image->img_ptr);
    free(data->image);
}

// Modify init_game function to initialize the new variable:
void init_game(t_data *data)
{
    data->is_minimap_fullscreen = 0;  // Initialize to mini mode
    // ... rest of the initialization ...
}