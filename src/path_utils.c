/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmar <kmar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 00:00:00 by kmar              #+#    #+#             */
/*   Updated: 2025/10/08 00:00:00 by kmar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

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

static void	add_neighbors(t_point *stack, int *top, t_point cur)
{
	t_point	next;

	next.x = cur.x + 1;
	next.y = cur.y;
	add_if_valid(stack, top, next);
	next.x = cur.x - 1;
	add_if_valid(stack, top, next);
	next.y = cur.y + 1;
	next.x = cur.x;
	add_if_valid(stack, top, next);
	next.y = cur.y - 1;
	add_if_valid(stack, top, next);
}

void	flood_fill(char **grid, t_point start, t_point size)
{
	t_point	stack[10000];
	t_point	cur;
	int		top;

	top = 0;
	stack[top++].x = start.x;
	stack[top - 1].y = start.y;
	while (top > 0)
	{
		cur = stack[--top];
		if (cur.x < 0 || cur.x >= size.x || cur.y < 0 || cur.y >= size.y)
			continue ;
		if (grid[cur.y][cur.x] == MAP_WALL || grid[cur.y][cur.x] == 'V')
			continue ;
		grid[cur.y][cur.x] = 'V';
		add_neighbors(stack, &top, cur);
	}
}

char	**copy_map(t_map *map)
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
