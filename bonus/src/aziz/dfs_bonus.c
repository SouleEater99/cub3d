/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:18:02 by aelkheta          #+#    #+#             */
/*   Updated: 2024/12/04 14:19:03 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	print_int(int **arr, int *len, int height)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (++j < height)
	{
		i = -1;
		while (++i < len[j])
		{
			printf("%d", arr[j][i]);
		}
		printf("\n");
	}
	printf("\n");
}

/// @brief DFS (Depth-First Search) function.
/// @param map
/// @param visited
/// @param x
/// @param y
/// @return
bool	dfs(t_map *map, int **visited, int x, int y)
{
	bool	up;
	bool	down;
	bool	left;
	bool	right;

	if (x < 0 || y < 0 || x >= map->map_line_len[y] || y >= map->map_height)
		return (false);
	if (visited[y][x] || map->map[y][x] == '1')
		return (true);
	if (x == 0 || y == 0 || x == map->map_line_len[y] || y == map->map_height
		- 1)
		return (false);
	visited[y][x] = 1;
	up = dfs(map, visited, x, y - 1);
	down = dfs(map, visited, x, y + 1);
	left = dfs(map, visited, x - 1, y);
	right = dfs(map, visited, x + 1, y);
	return (up && down && left && right);
}
