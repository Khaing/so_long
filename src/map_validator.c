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
			if ((y == 0 || y == map->height - 1 || 
				 x == 0 || x == map->width - 1) && 
				map->grid[y][x] != MAP_WALL)
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

static void	flood_fill(char **grid, int x, int y, int width, int height)
{
	if (x < 0 || x >= width || y < 0 || y >= height || 
		grid[y][x] == MAP_WALL || grid[y][x] == 'V')
		return;
	
	grid[y][x] = 'V';
	flood_fill(grid, x + 1, y, width, height);
	flood_fill(grid, x - 1, y, width, height);
	flood_fill(grid, x, y + 1, width, height);
	flood_fill(grid, x, y - 1, width, height);
}

static char	**copy_map(t_map *map)
{
	char	**copy;
	int		y;

	copy = malloc(sizeof(char *) * (map->height + 1));
	if (!copy)
		return (NULL);
	
	y = 0;
	while (y < map->height)
	{
		copy[y] = malloc(strlen(map->grid[y]) + 1);
		if (!copy[y])
		{
			while (--y >= 0)
				free(copy[y]);
			free(copy);
			return (NULL);
		}
		strcpy(copy[y], map->grid[y]);
		y++;
	}
	copy[y] = NULL;
	return (copy);
}

int	is_valid_path(t_map *map)
{
	char	**grid_copy;
	int		x;
	int		y;
	int		collectibles_found;
	int		exit_found;

	grid_copy = copy_map(map);
	if (!grid_copy)
		return (0);
	
	flood_fill(grid_copy, map->player.x, map->player.y, map->width, map->height);
	
	collectibles_found = 0;
	exit_found = 0;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (grid_copy[y][x] == 'V')
			{
				if (map->grid[y][x] == MAP_COLLECTIBLE)
					collectibles_found++;
				else if (map->grid[y][x] == MAP_EXIT)
					exit_found = 1;
			}
			x++;
		}
		y++;
	}
	
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