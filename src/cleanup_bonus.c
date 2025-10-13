/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmar <kmar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 12:10:23 by kmar              #+#    #+#             */
/*   Updated: 2025/10/07 12:10:50 by kmar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

static void	destroy_sprites(t_game *game)
{
	int	i;

	if (game->sprites.wall)
		mlx_destroy_image(game->mlx, game->sprites.wall);
	if (game->sprites.empty)
		mlx_destroy_image(game->mlx, game->sprites.empty);
	if (game->sprites.exit)
		mlx_destroy_image(game->mlx, game->sprites.exit);
	i = 0;
	while (i < 4)
	{
		if (game->sprites.collectible[i])
			mlx_destroy_image(game->mlx, game->sprites.collectible[i]);
		if (game->sprites.player[i])
			mlx_destroy_image(game->mlx, game->sprites.player[i]);
		i++;
	}
	i = 0;
	while (i < 2)
	{
		if (game->sprites.enemy[i])
			mlx_destroy_image(game->mlx, game->sprites.enemy[i]);
		i++;
	}
}

void	cleanup_game(t_game *game)
{
	if (!game)
		return ;
	destroy_sprites(game);
	if (game->window && game->mlx)
		mlx_destroy_window(game->mlx, game->window);
	if (game->map.grid)
		free_map(game->map.grid);
	if (game->enemies)
		free(game->enemies);
}
