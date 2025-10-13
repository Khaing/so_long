/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmar <kmar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 00:00:00 by kmar              #+#    #+#             */
/*   Updated: 2025/10/08 00:00:00 by kmar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	process_map_char(t_map *map, char c, int x, int y)
{
	if (c == MAP_PLAYER)
	{
		if (map->player.x != -1)
			return (0);
		map->player.x = x;
		map->player.y = y;
	}
	else if (c == MAP_EXIT)
	{
		if (map->exit.x != -1)
			return (0);
		map->exit.x = x;
		map->exit.y = y;
	}
	else if (c == MAP_COLLECTIBLE)
		map->collectibles++;
	else if (c != MAP_WALL && c != MAP_EMPTY)
		return (0);
	return (1);
}

void	init_map_data(t_map *map)
{
	map->width = 0;
	map->height = 0;
	map->collectibles = 0;
	map->collected = 0;
	map->player.x = -1;
	map->player.y = -1;
	map->exit.x = -1;
	map->exit.y = -1;
}
