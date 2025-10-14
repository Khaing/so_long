/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_enemy_init_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmar <kmar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:40:55 by kmar              #+#    #+#             */
/*   Updated: 2025/10/14 20:46:30 by kmar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

static void	init_enemy_data(t_game *game)
{
	game->sprites.enemy[0] = NULL;
	game->sprites.enemy[1] = NULL;
	game->map.grid = NULL;
}

void	init_game_data(t_game *game)
{
	int	i;

	game->mlx = NULL;
	game->window = NULL;
	game->moves = 0;
	game->game_won = 0;
	game->game_over = 0;
	game->frame_counter = 0;
	game->camera.x = 0;
	game->camera.y = 0;
	game->camera.offset_x = 0;
	game->camera.offset_y = 0;
	game->enemies = NULL;
	game->enemy_count = 0;
	game->sprites.wall = NULL;
	game->sprites.empty = NULL;
	game->sprites.exit = NULL;
	i = 0;
	while (i < 4)
	{
		game->sprites.collectible[i] = NULL;
		game->sprites.player[i] = NULL;
		i++;
	}
	init_enemy_data(game);
}
