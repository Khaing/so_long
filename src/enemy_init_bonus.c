/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_init_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmar <kmar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 00:00:00 by kmar              #+#    #+#             */
/*   Updated: 2025/10/13 00:00:00 by kmar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

static int	count_enemies(t_game *game)
{
	int	count;
	int	y;
	int	x;

	count = 0;
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (game->map.grid[y][x] == MAP_ENEMY)
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

static void	add_enemy(t_game *game, int x, int y, int *idx)
{
	game->enemies[*idx].pos.x = x;
	game->enemies[*idx].pos.y = y;
	game->enemies[*idx].direction = 0;
	game->enemies[*idx].axis = 0;
	game->enemies[*idx].patrol_start = x;
	game->enemies[*idx].patrol_end = x;
	(*idx)++;
}

int	init_enemies(t_game *game)
{
	int	idx;
	int	y;
	int	x;

	game->enemy_count = count_enemies(game);
	if (game->enemy_count == 0)
		return (1);
	game->enemies = malloc(sizeof(t_enemy) * game->enemy_count);
	if (!game->enemies)
		return (0);
	idx = 0;
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (game->map.grid[y][x] == MAP_ENEMY)
				add_enemy(game, x, y, &idx);
			x++;
		}
		y++;
	}
	return (1);
}
