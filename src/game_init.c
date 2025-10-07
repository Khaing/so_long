/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmar <kmar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 12:11:27 by kmar              #+#    #+#             */
/*   Updated: 2025/10/07 13:36:08 by kmar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	init_game_data(t_game *game)
{
	int	i;

	game->mlx = NULL;
	game->window = NULL;
	game->moves = 0;
	game->game_won = 0;
	game->frame_counter = 0;
	game->camera.x = 0;
	game->camera.y = 0;
	game->camera.offset_x = 0;
	game->camera.offset_y = 0;
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
	game->map.grid = NULL;
}

static int	create_window(t_game *game)
{
	int	window_width;
	int	window_height;

	window_width = game->map.width * TILE_SIZE;
	window_height = game->map.height * TILE_SIZE;
	if (window_width > WINDOW_WIDTH)
		window_width = WINDOW_WIDTH;
	if (window_height > WINDOW_HEIGHT)
		window_height = WINDOW_HEIGHT;
	game->window = mlx_new_window(game->mlx, window_width, window_height,
			"so_long");
	if (!game->window)
		return (0);
	return (1);
}

static int	setup_hooks(t_game *game)
{
	mlx_hook(game->window, 2, 1L << 0, handle_keypress, game);
	mlx_hook(game->window, 17, 1L << 17, handle_close, game);
	mlx_loop_hook(game->mlx, animation_loop, game);
	return (1);
}

int	init_game(t_game *game, char *map_file)
{
	init_game_data(game);
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		print_error("Failed to initialize MLX");
		return (0);
	}
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
	if (!create_window(game))
	{
		print_error("Failed to create window");
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
