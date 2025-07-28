#include "../includes/so_long.h"

static void	*create_simple_sprite(t_game *game, int color)
{
	void	*img;
	char	*data;
	int		bpp;
	int		size_line;
	int		endian;
	int		x;
	int		y;

	img = mlx_new_image(game->mlx, TILE_SIZE, TILE_SIZE);
	if (!img)
		return (NULL);
	
	data = mlx_get_data_addr(img, &bpp, &size_line, &endian);
	if (!data)
	{
		mlx_destroy_image(game->mlx, img);
		return (NULL);
	}
	
	y = 0;
	while (y < TILE_SIZE)
	{
		x = 0;
		while (x < TILE_SIZE)
		{
			*(int *)(data + (y * size_line + x * (bpp / 8))) = color;
			x++;
		}
		y++;
	}
	
	return (img);
}

static void	*create_simple_player(t_game *game, int frame __attribute__((unused)))
{
	void	*img;
	char	*data;
	int		bpp;
	int		size_line;
	int		endian;
	int		x;
	int		y;
	int		color;

	img = mlx_new_image(game->mlx, TILE_SIZE, TILE_SIZE);
	if (!img)
		return (NULL);
	
	data = mlx_get_data_addr(img, &bpp, &size_line, &endian);
	if (!data)
	{
		mlx_destroy_image(game->mlx, img);
		return (NULL);
	}
	
	y = 0;
	while (y < TILE_SIZE)
	{
		x = 0;
		while (x < TILE_SIZE)
		{
			if (x >= 16 && x <= 48 && y >= 16 && y <= 48)
			{
				if ((x >= 20 && x <= 24 && y >= 20 && y <= 24) || 
					(x >= 40 && x <= 44 && y >= 20 && y <= 24))
					color = 0x000000;
				else
					color = 0x00FF00;
			}
			else
				color = 0x87CEEB;
			
			*(int *)(data + (y * size_line + x * (bpp / 8))) = color;
			x++;
		}
		y++;
	}
	
	return (img);
}

int	load_sprites_simple(t_game *game)
{
	int	i;

	game->sprites.width = TILE_SIZE;
	game->sprites.height = TILE_SIZE;
	game->sprites.current_frame = 0;
	game->sprites.frame_count = 4;
	
	game->sprites.wall = create_simple_sprite(game, 0x8B4513);
	if (!game->sprites.wall)
		return (0);
	
	game->sprites.empty = create_simple_sprite(game, 0x87CEEB);
	if (!game->sprites.empty)
		return (0);
	
	i = 0;
	while (i < 4)
	{
		game->sprites.collectible[i] = create_simple_sprite(game, 0xFFD700);
		if (!game->sprites.collectible[i])
			return (0);
		i++;
	}
	
	game->sprites.exit = create_simple_sprite(game, 0xFF0000);
	if (!game->sprites.exit)
		return (0);
	
	i = 0;
	while (i < 4)
	{
		game->sprites.player[i] = create_simple_player(game, i);
		if (!game->sprites.player[i])
			return (0);
		i++;
	}
	
	return (1);
}