/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_loader_norm.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmar <kmar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 12:29:46 by kmar              #+#    #+#             */
/*   Updated: 2025/10/07 12:29:50 by kmar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int	load_collectibles(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		game->sprites.collectible[i] = create_fish(game->mlx, TILE_SIZE);
		if (!game->sprites.collectible[i])
			return (0);
		i++;
	}
	return (1);
}

static int	load_player_sprites(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		game->sprites.player[i] = create_dolphin(game->mlx, TILE_SIZE);
		if (!game->sprites.player[i])
			return (0);
		i++;
	}
	return (1);
}

static int	load_basic_sprites(t_game *game)
{
	game->sprites.wall = create_coral(game->mlx, TILE_SIZE);
	if (!game->sprites.wall)
		return (0);
	game->sprites.empty = create_ocean(game->mlx, TILE_SIZE);
	if (!game->sprites.empty)
		return (0);
	game->sprites.exit = create_exit_gate(game->mlx, TILE_SIZE);
	if (!game->sprites.exit)
		return (0);
	return (1);
}

int	load_sprites(t_game *game)
{
	game->sprites.width = TILE_SIZE;
	game->sprites.height = TILE_SIZE;
	game->sprites.current_frame = 0;
	game->sprites.frame_count = 4;
	if (!load_basic_sprites(game))
		return (0);
	if (!load_collectibles(game))
		return (0);
	if (!load_player_sprites(game))
		return (0);
	return (1);
}
