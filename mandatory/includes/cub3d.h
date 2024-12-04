/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 04:00:30 by ael-maim          #+#    #+#             */
/*   Updated: 2024/12/04 14:14:28 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <keycodes.h>
# include <libft.h>
# include <math.h>
# include <mlx.h>
# include <mlx_int.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define WIDTH 800
# define HIGH 600

# define MAX_HEIGHT 250
# define MAX_WIDTH 250

# define CUBE_TILE 256
# define TEXTURE_TILE 256

# define PLAYER_TILE 10
# define WALL_STRIP 1
# define WALL_DISTANCE 384
# define BLACK 0x00000000
# define WHITE 0x00FFFFFF
# define RED 0x00FF0000
# define YELLOW 0x00FFFF00
# define BLUE 0x000000FF
# define GREEN 0x0000FF00
# define CEILING 0x00E11E1E
# define FLOOR 0x00DC6400

# ifndef PI
#  define PI 3.14159265358979323846
# endif

# define BRED "\e[1;31m"
# define BGRN "\e[1;32m"
# define COLOR_RESET "\e[0m"

# define PLAYER_DIR "NSEW"
# define SUPPORTED_CHARS "NSEW01\t\n "

# define NUM_TEXTURES 4
# define NUM_COLORS 2

# define SCREEN_WIDTH WIDTH
# define SCREEN_HEIGHT HIGH

# define ROT_SPEED 0.02
# define MOVE_SPEED 4

typedef struct s_minimap
{
	double			start_x;
	double			start_y;

	double			end_x;
	double			end_y;
}					t_minimap;

typedef struct s_map
{
	char			**map;
	int				map_height;
	int				map_width;
	int				map_start;
	int				*map_line_len;

	char			*no_texture_path;
	char			*so_texture_path;
	char			*we_texture_path;
	char			*ea_texture_path;

	int				floor_color;
	int				ceiling_color;
}					t_map;

typedef struct s_image
{
	void			*img_ptr;
	void			*img_data;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	int				width;
	int				height;
}					t_image;

typedef struct s_player
{
	double			dir_x;
	double			dir_y;
	double			player_x;
	double			player_y;
	void			*current_img;
	t_image			*frames;
	int				frames_num;
	char			*frames_path;
}					t_player;

typedef struct s_data
{
	int				i;

	unsigned short	img_width;
	unsigned short	img_height;
	unsigned short	row;
	unsigned short	col;

	void			*mlx_ptr;
	void			*win_ptr;

	unsigned int	color;
	int				is_face_down;
	int				is_face_right;
	double			distance;
	double			correct_distance;
	double			wall_slice_high;
	double			wall_hit_x;
	double			wall_hit_y;
	int				is_hit_virt;
	int				num_rays;

	double			plan_distanced;
	int				start;
	int				end;

	int				flag;

	double			x_player;
	double			y_player;
	int				turn_direction;
	int				walk_direction;
	int				strafe_direction;
	double			turn_speed;
	double			move_speed;
	double			move_step;
	double			player_angle;
	double			player_distance;
	double			player_wallhit_x;
	double			player_wallhit_y;

	double			factor_scale_map;

	t_image			projection_img;
	int				start_player_x;
	int				start_player_y;
	int				player_offset;

	t_map			map;
	double			player_x;
	double			player_y;
	int16_t			player_dir;

	char			*trimmed;
	char			**map_lines;

	char			*no_texture_path;
	char			*so_texture_path;
	char			*we_texture_path;
	char			*ea_texture_path;
	char			*dr_texture_path;

	t_image			*image;
	t_image			*textures[NUM_TEXTURES];
	char			*textures_path[NUM_TEXTURES];
	t_player		player;

	double			dist_x;
	double			dist_y;
	double			y_increment;
	double			x_increment;

	double			fov;
	double			steps;
	int				step;

	int				textures_found;
	int				colors_found;

	double			ystep;
	double			xstep;
	char			**lines;
}					t_data;

int					init_data(t_data *data, int ac, char **av);
void				init_mlx(t_data *data);
void				ft_free_all(char *Msg, t_data *data, int Exit_Status);
int					ft_key_destroy(void *Param);
int					ft_loop_hook(void *Param);
void				ft_write_cub(t_data *data, int x, int y, int Color);
void				ft_create_pojection_img(t_data *data);
void				my_mlx_pixel_put(t_image *img, int x, int y, int color);
int					ft_get_color(t_image *Img, int x, int y);
void				ft_write_line(t_data *data, int dx, int dy, int color);
int					ft_is_angle_facing_down(double angle);
int					ft_is_angle_facing_right(double angle);
int					ft_board_protect(int Width, int High, int x, int y);
int					ft_is_a_wall(t_data *data, int x, int y);
int					ft_is_player_inside_wall(t_data *data);
double				ft_normalize_angle(double angle);
int					ft_key_press(int key, void *Param);
int					ft_key_release(int key, void *Param);
void				ft_update_data(t_data *data);
void				ft_update_image(t_data *data);
double				ft_calc_distance(t_data *data, double x, double y);
void				ft_cast_all_rays(t_data *data);
void				ft_get_wall_hit(t_data *data, double Angle);
void				ft_get_horz_hit(t_data *data, double Angle, double *x,
						double *y);
void				ft_get_virt_hit(t_data *data, double Angle, double *x,
						double *y);
void				ft_write_projection(t_data *data, int i);
void				ft_write_wall(t_data *data, int i);
void				ft_write_ceiling(t_data *data, int i, int color);
void				ft_write_floor(t_data *data, int i, int color);
void				ft_get_texture_color(t_data *data, int j);
void				ft_write_player_wall_hit(t_data *data);

void				draw_minimap(t_data *data);
int					parse_map(t_data *data, int ac, char **av);
int					shade_walls(int color, double distance);
int					shade_walls(int color, double distance);
void				render_sprites(t_data *data);
void				init_player_sprites(t_data *data, char *dir_path,
						int frames_num);
void				print_error(char *error_str, char *file, int line);
int					mouse_events(int button, int x, int y, t_data *data);
void				mouse_hooks(t_data *data);
void				free_array(char **arr);
int					get_color(char **colors);
int					check_color_format(const char *str_color);
int64_t				parse_color(const char *str_color);
void				validate_color(t_data *data, char **parts,
						int *current_line, int *colors_found);
int					arr_len(char **array);
int					ft_isspace(int c);
void				print_error(char *error_str, char *file, int line);
void				ft_panic(int line_num, int col_num, const char *line,
						void *data);
void				free_int_array(int **int_array, int arr_len);
void				free_parse_allocated(t_data *data, char **parts, char *message);
void				validate_texture(t_data *data, char **parts,
						int *textures_found);
char				**get_texture_ptr(t_data *data, char *texture_dir);
char				*parse_texture(char *texture_path);
t_image				*load_texture(void *mlx, char *filename);

int					check_extension(const char *file_path,
						const char *extension);
void				draw_tile(t_data *data, double x, double y, int color);
void				draw_ray_line(t_data *data, t_image *image, double end_x,
						double end_y);
void				draw_tile_within_bounds(t_data *data, int map_x, int map_y);
char				*get_img_address(t_image *image);
void				init_player_sprites(t_data *data, char *dir_path,
						int frames_num);
void				draw_pixel(t_image *image, int dx, int dy,
						int sprite_pixel);
bool				dfs(t_map *map, int **visited, int x, int y);
int					arr_len(char **array);
int					ft_isspace(int c);
void				print_error(char *error_str, char *file, int line);
void				ft_panic(int line_num, int col_num, const char *line,
						void *data);
bool				is_empty_line(const char *line);
int					is_empty_map(const char *map_path, int *height);
char				**read_lines(int fd, int *height);
char				**read_map_lines(const char *map_path, int *height);
void				check_args_num(t_data *data, char **parts,
						int *current_line);
bool				parse_metadata(t_data *data, char **map_lines,
						int map_heigh, int *current_line);
void				check_map_characters(t_data *data, int i, int j,
						bool *is_player_found);
bool				validate_map(t_data *data);
void				print_map(t_map *map);
void				print_str(char *str, int index);
int					check_first_last(t_data *data, char **map, int map_height);
int					validate_map_borders(t_data *data, char **map, int height);
char				**copy_array(char **array, int array_len);
int					**init_int_arr(int *lines_len, int arr_len);
int					check_left_right(t_data *data, char **map, int height);
void				check_map_lr(t_data *data, int height, int i, int j);
void				destroy_images(void *mlx_ptr, t_image **images,
						int images_num);

#endif
