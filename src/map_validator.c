/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmar <kmar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 12:20:25 by kmar              #+#    #+#             */
/*   Updated: 2025/10/07 12:27:19 by kmar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int	is_wall_enclosed(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if ((y == 0 || y == map->height - 1
					|| x == 0 || x == map->width - 1)
				&& map->grid[y][x] != MAP_WALL)
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

static void	count_reachable(t_map *map, char **grid, int *c_found, int *e_found)
{
	int	x;
	int	y;

	*c_found = 0;
	*e_found = 0;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (grid[y][x] == 'V')
			{
				if (map->grid[y][x] == MAP_COLLECTIBLE)
					(*c_found)++;
				else if (map->grid[y][x] == MAP_EXIT)
					*e_found = 1;
			}
			x++;
		}
		y++;
	}
}

int	is_valid_path(t_map *map)
{
	char	**grid_copy;
	int		collectibles_found;
	int		exit_found;
	t_point	start;
	t_point	size;

	grid_copy = copy_map(map);
	if (!grid_copy)
		return (0);
	start.x = map->player.x;
	start.y = map->player.y;
	size.x = map->width;
	size.y = map->height;
	flood_fill(grid_copy, start, size);
	count_reachable(map, grid_copy, &collectibles_found, &exit_found);
	free_map(grid_copy);
	return (collectibles_found == map->collectibles && exit_found);
}

int	validate_map(t_map *map)
{
	if (!map || !map->grid)
		return (0);
	if (map->width < 3 || map->height < 3)
		return (0);
	if (!is_wall_enclosed(map))
		return (0);
	if (!is_valid_path(map))
		return (0);
	return (1);
}
