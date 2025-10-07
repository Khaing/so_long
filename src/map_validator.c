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

static void	add_if_valid(t_point *s, int *t, t_point p)
{
	if (p.x < 0 || p.y < 0)
		return ;
	if (*t >= 9999)
		return ;
	s[*t].x = p.x;
	s[*t].y = p.y;
	(*t)++;
}

static void	flood_fill(char **grid, int sx, int sy, int w, int h)
{
	t_point	stack[10000];
	t_point	cur;
	t_point	next;
	int		top;

	top = 0;
	stack[top++].x = sx;
	stack[top - 1].y = sy;
	while (top > 0)
	{
		cur = stack[--top];
		if (cur.x < 0 || cur.x >= w || cur.y < 0 || cur.y >= h)
			continue ;
		if (grid[cur.y][cur.x] == MAP_WALL || grid[cur.y][cur.x] == 'V')
			continue ;
		grid[cur.y][cur.x] = 'V';
		next.x = cur.x + 1;
		next.y = cur.y;
		add_if_valid(stack, &top, next);
		next.x = cur.x - 1;
		add_if_valid(stack, &top, next);
		next.y = cur.y + 1;
		next.x = cur.x;
		add_if_valid(stack, &top, next);
		next.y = cur.y - 1;
		add_if_valid(stack, &top, next);
	}
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
	flood_fill(grid_copy, map->player.x, map->player.y,
		map->width, map->height);
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
