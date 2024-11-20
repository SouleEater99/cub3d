/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_visualized.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 08:46:41 by aelkheta          #+#    #+#             */
/*   Updated: 2024/11/20 09:55:00 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mandatory/includes/mlx.h"
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#define CELL_SIZE   40
#define WIN_WIDTH   800
#define WIN_HEIGHT  600

typedef struct
{
    void *mlx;
    void *win;
    char **map;
    int map_width;
    int map_height;
    int **visited;
} t_visual;

void draw_map(t_visual *vis)
{
    for (int y = 0; y < vis->map_height; y++)
    {
        for (int x = 0; x < vis->map_width; x++)
        {
            int color;
            if (vis->map[y][x] == '1') color = 0x808080; // Gray for walls
            else if (vis->visited[y][x]) color = 0xFF0000; // Red for visited
            else color = 0xFFFFFF; // White for empty spaces

            for (int py = 0; py < CELL_SIZE; py++)
            {
                for (int px = 0; px < CELL_SIZE; px++)
                {
                    mlx_pixel_put(vis->mlx, vis->win, x * CELL_SIZE + px, y * CELL_SIZE + py, color);
                }
            }
        }
    }
}

bool dfs(t_visual *vis, int x, int y)
{
    if (x < 0 || y < 0 || x >= vis->map_width || y >= vis->map_height)
        return false;

    if (vis->visited[y][x] || vis->map[y][x] == '1')
        return true;

    if (x == 0 || y == 0 || x == vis->map_width - 1 || y == vis->map_height - 1)
        return false;

    vis->visited[y][x] = 1; // mark it as visited

    draw_map(vis);

    bool up = dfs(vis, x, y - 1);
    bool down = dfs(vis, x, y + 1);
    bool left = dfs(vis, x - 1, y);
    bool right = dfs(vis, x + 1, y);

    return (up && down && left && right);
}

# define ESC_KEY 65307

int close_func(int keycode, t_visual *vis)
{
    (void) vis;
    if (keycode == ESC_KEY)
        exit (0);
    return (0);
}

int main() {
    t_visual vis;

    vis.mlx = mlx_init();
    vis.win = mlx_new_window(vis.mlx, WIN_WIDTH, WIN_HEIGHT, "DFS Visualization");

    vis.map = (char *[]) {
        "1111111111111",
        "1001000100101",
        "1100110110001",
        "1001000000001",
        "1100100000101",
        "1010010010011",
        "1000000000001",
        "1101010000001",
        "1000000000001",
        "1010010001101",
        "1111111111111",
        
    };
    vis.map_width = 14;
    vis.map_height = 11;

    vis.visited = malloc(vis.map_height * sizeof(int *));
    for (int i = 0; i < vis.map_height; i++)
    {
        vis.visited[i] = calloc(vis.map_width, sizeof(int));
    }

    dfs(&vis, 5, 4);

    for (int i = 0; i < vis.map_height; i++) {
        free(vis.visited[i]);
    }

    mlx_hook(vis.mlx, 17, 0, close_func, &vis);
    mlx_loop(vis.mlx);

    free(vis.visited);
}
