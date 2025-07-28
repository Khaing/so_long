#include "../includes/so_long.h"

static void	*get_sprite_for_tile(t_game *game, char tile, int x, int y)
{
	if (x == game->map.player.x && y == game->map.player.y)
		return (game->sprites.player[game->sprites.current_frame]);
	
	if (tile == MAP_WALL)
		return (game->sprites.wall);
	else if (tile == MAP_COLLECTIBLE)
		return (game->sprites.collectible[game->sprites.current_frame]);
	else if (tile == MAP_EXIT)
		return (game->sprites.exit);
	else
		return (game->sprites.empty);
}

static void	render_tile(t_game *game, int map_x, int map_y, int screen_x, int screen_y)
{
	void	*sprite;

	if (map_x >= game->map.width || map_y >= game->map.height || map_x < 0 || map_y < 0)
		return;
	
	sprite = get_sprite_for_tile(game, game->map.grid[map_y][map_x], map_x, map_y);
	if (!sprite)
		return;
	
	mlx_put_image_to_window(game->mlx, game->window, sprite, screen_x, screen_y);
}

static void	render_hud(t_game *game)
{
	char	moves_text[50];
	char	collectibles_text[50];

	sprintf(moves_text, "Moves: %d", game->moves);
	sprintf(collectibles_text, "Collectibles: %d/%d", 
			game->map.collected, game->map.collectibles);
	
	mlx_string_put(game->mlx, game->window, 10, 20, 0xFFFFFF, moves_text);
	mlx_string_put(game->mlx, game->window, 10, 40, 0xFFFFFF, collectibles_text);
	
	if (game->game_won)
		mlx_string_put(game->mlx, game->window, 10, 60, 0x00FF00, "YOU WIN!");
}

void	update_camera(t_game *game)
{
	int	window_tiles_x;
	int	window_tiles_y;
	int	target_camera_x;
	int	target_camera_y;

	window_tiles_x = WINDOW_WIDTH / TILE_SIZE;
	window_tiles_y = WINDOW_HEIGHT / TILE_SIZE;
	
	if (game->map.width <= window_tiles_x)
	{
		target_camera_x = 0;
	}
	else
	{
		target_camera_x = game->map.player.x - window_tiles_x / 2;
		if (target_camera_x < 0)
			target_camera_x = 0;
		if (target_camera_x + window_tiles_x > game->map.width)
			target_camera_x = game->map.width - window_tiles_x;
	}
	
	if (game->map.height <= window_tiles_y)
	{
		target_camera_y = 0;
	}
	else
	{
		target_camera_y = game->map.player.y - window_tiles_y / 2;
		if (target_camera_y < 0)
			target_camera_y = 0;
		if (target_camera_y + window_tiles_y > game->map.height)
			target_camera_y = game->map.height - window_tiles_y;
	}
	
	game->camera.x = target_camera_x;
	game->camera.y = target_camera_y;
	game->camera.offset_x = target_camera_x * TILE_SIZE;
	game->camera.offset_y = target_camera_y * TILE_SIZE;
}

void	render_game(t_game *game)
{
	int	screen_x;
	int	screen_y;
	int	map_x;
	int	map_y;
	int	window_tiles_x;
	int	window_tiles_y;
	int	max_screen_x;
	int	max_screen_y;

	if (!game || !game->window)
		return;
	
	update_camera(game);
	mlx_clear_window(game->mlx, game->window);
	
	window_tiles_x = WINDOW_WIDTH / TILE_SIZE;
	window_tiles_y = WINDOW_HEIGHT / TILE_SIZE;
	
	max_screen_x = window_tiles_x;
	if (game->map.width - game->camera.x < window_tiles_x)
		max_screen_x = game->map.width - game->camera.x;
	
	max_screen_y = window_tiles_y;
	if (game->map.height - game->camera.y < window_tiles_y)
		max_screen_y = game->map.height - game->camera.y;
	
	screen_y = 0;
	while (screen_y < max_screen_y)
	{
		screen_x = 0;
		while (screen_x < max_screen_x)
		{
			map_x = game->camera.x + screen_x;
			map_y = game->camera.y + screen_y;
			render_tile(game, map_x, map_y, screen_x * TILE_SIZE, screen_y * TILE_SIZE);
			screen_x++;
		}
		screen_y++;
	}
	
	render_hud(game);
}