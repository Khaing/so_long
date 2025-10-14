/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmar <kmar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 12:11:27 by kmar              #+#    #+#             */
/*   Updated: 2025/10/14 14:41:58 by kmar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

static int	setup_hooks(t_game *game)
{
	mlx_hook(game->window, 2, 1L << 0, handle_keypress, game);
	mlx_hook(game->window, 17, 1L << 17, handle_close, game);
	mlx_loop_hook(game->mlx, animation_loop, game);
	return (1);
}

static int	init_map_and_validate(t_game *game, char *map_file)
{
	if (!parse_map(game, map_file))
	{
		print_error("Invalid map file");
		cleanup_game(game);
		return (0);
	}
	if (!validate_map(&game->map))
	{
		print_error("Map validation failed");
		cleanup_game(game);
		return (0);
	}
	return (1);
}

static int	init_mlx_and_window(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		print_error("Failed to initialize MLX");
		cleanup_game(game);
		return (0);
	}
	if (!create_window(game))
	{
		print_error("Failed to create window");
		cleanup_game(game);
		return (0);
	}
	return (1);
}

int	init_game(t_game *game, char *map_file)
{
	init_game_data(game);
	if (!init_map_and_validate(game, map_file))
		return (0);
	if (!init_mlx_and_window(game))
		return (0);
	if (!init_enemies(game))
	{
		print_error("Failed to initialize enemies");
		cleanup_game(game);
		return (0);
	}
	if (!load_sprites(game))
	{
		print_error("Failed to load sprites");
		cleanup_game(game);
		return (0);
	}
	if (!setup_hooks(game))
	{
		print_error("Failed to setup hooks");
		cleanup_game(game);
		return (0);
	}
	return (1);
}
