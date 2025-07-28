#include "../includes/so_long.h"

static void	*create_ocean_background(t_game *game)
{
	void	*img;
	char	*data;
	int		bpp;
	int		size_line;
	int		endian;
	int		x;
	int		y;
	int		color;
	int		base_color;

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
			base_color = 0x006994;
			if ((x + y) % 20 < 3)
				color = 0x4A90E2;
			else if ((x % 15 == 0 && y % 10 < 2) || (y % 15 == 0 && x % 10 < 2))
				color = 0x87CEEB;
			else if ((x - y) % 25 < 2)
				color = 0x5DADE2;
			else
				color = base_color + (y % 8) * 0x010203;
			*(int *)(data + (y * size_line + x * (bpp / 8))) = color;
			x++;
		}
		y++;
	}
	
	return (img);
}

static void	*create_coral_wall(t_game *game)
{
	void	*img;
	char	*data;
	int		bpp;
	int		size_line;
	int		endian;
	int		x;
	int		y;
	int		color;
	int		dist_center;

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
			dist_center = (x - 32) * (x - 32) + (y - 32) * (y - 32);
			if (dist_center < 15 * 15)
				color = 0xFF69B4;
			else if (dist_center < 20 * 20)
				color = 0xFF1493;
			else if ((x + y) % 12 < 4)
				color = 0xFF6347;
			else if ((x * 3 + y * 2) % 16 < 6)
				color = 0xFF4500;
			else if (y % 8 < 2 && x % 6 < 2)
				color = 0xFFA500;
			else
				color = 0xDC143C;
			*(int *)(data + (y * size_line + x * (bpp / 8))) = color;
			x++;
		}
		y++;
	}
	
	return (img);
}

static void	*create_exit_sprite(t_game *game)
{
	void	*img;
	char	*data;
	int		bpp;
	int		size_line;
	int		endian;
	int		x;
	int		y;
	int		color;
	int		dist;

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
			color = 0x006994;
			
			if (x >= 20 && x <= 44 && y >= 8 && y <= 12)
				color = 0x228B22;
			else if (x >= 20 && x <= 44 && y >= 52 && y <= 56)
				color = 0x228B22;
			else if (x >= 10 && x <= 14 && y >= 16 && y <= 48)
				color = 0x32CD32;
			else if (x >= 50 && x <= 54 && y >= 16 && y <= 48)
				color = 0x32CD32;
			else if (x >= 28 && x <= 36 && y >= 16 && y <= 48)
				color = 0x00FF7F;
			
			dist = (x - 32) * (x - 32) + (y - 32) * (y - 32);
			if (dist < 8 * 8)
				color = 0x90EE90;
			else if (dist < 12 * 12 && (x + y) % 4 == 0)
				color = 0x98FB98;
			
			*(int *)(data + (y * size_line + x * (bpp / 8))) = color;
			x++;
		}
		y++;
	}
	
	return (img);
}

static void	*create_dolphin_sprite(t_game *game, int frame)
{
	void	*img;
	char	*data;
	int		bpp;
	int		size_line;
	int		endian;
	int		x;
	int		y;
	int		color;
	float	swim_phase;
	int		tail_bend;
	int		fin_wave;
	int		dx, dy;
	float	body_dist, head_dist, tail_dist;

	img = mlx_new_image(game->mlx, TILE_SIZE, TILE_SIZE);
	if (!img)
		return (NULL);
	
	data = mlx_get_data_addr(img, &bpp, &size_line, &endian);
	if (!data)
	{
		mlx_destroy_image(game->mlx, img);
		return (NULL);
	}
	
	swim_phase = (frame * 0.3f);
	tail_bend = (int)(sin(swim_phase) * 3.0f);
	fin_wave = (int)(sin(swim_phase + 1.5f) * 1.5f);
	
	y = 0;
	while (y < TILE_SIZE)
	{
		x = 0;
		while (x < TILE_SIZE)
		{
			color = 0x006994;
			
			// Dolphin head (rounded nose)
			dx = x - 8;
			dy = y - 32;
			head_dist = sqrt(dx * dx + dy * dy * 1.5f);
			if (head_dist < 6 && x >= 4 && x <= 14)
			{
				if (head_dist < 4)
					color = 0x87CEEB;
				else
					color = 0x5DADE2;
			}
			
			// Main body (streamlined torpedo shape)
			dx = x - 28;
			dy = y - 32;
			body_dist = sqrt((dx * dx) / 3.0f + (dy * dy) / 1.2f);
			if (body_dist < 12 && x >= 12 && x <= 45)
			{
				if (dy > 0)  // Lower body - lighter
				{
					if (body_dist < 8)
						color = 0x87CEEB;
					else
						color = 0x5DADE2;
				}
				else  // Upper body - darker
				{
					if (body_dist < 8)
						color = 0x5DADE2;
					else
						color = 0x4A90E2;
				}
			}
			
			// Tail section with bend
			if (x >= 45 && x <= 58)
			{
				int tail_y = 32 + (tail_bend * (x - 45)) / 8;
				tail_dist = abs(y - tail_y);
				if (tail_dist <= 8 - (x - 45) / 2)
				{
					if (tail_dist <= 3)
						color = 0x5DADE2;
					else
						color = 0x4A90E2;
				}
			}
			
			// Tail fluke (V-shaped)
			if (x >= 56 && x <= 60)
			{
				int tail_center = 32 + tail_bend;
				int fluke_spread = (x - 56) * 2;
				if (abs(y - (tail_center - fluke_spread)) <= 2 || 
					abs(y - (tail_center + fluke_spread)) <= 2)
					color = 0x4A90E2;
			}
			
			// Dorsal fin
			if (x >= 25 && x <= 32 && y >= 22 && y <= 28)
			{
				int fin_height = 28 - y;
				if (abs(x - 28) <= fin_height - fin_wave)
					color = 0x4A90E2;
			}
			
			// Eye
			if (x >= 14 && x <= 16 && y >= 29 && y <= 31)
				color = 0x000000;
			if (x == 15 && y == 30)
				color = 0xFFFFFF;
			
			*(int *)(data + (y * size_line + x * (bpp / 8))) = color;
			x++;
		}
		y++;
	}
	
	return (img);
}

static void	*create_fish_sprite(t_game *game, int frame)
{
	void	*img;
	char	*data;
	int		bpp;
	int		size_line;
	int		endian;
	int		x;
	int		y;
	int		color;
	float	swim_phase;
	int		body_sway;
	int		fin_wave;
	int		shine_pos;
	int		dx, dy, dist;

	img = mlx_new_image(game->mlx, TILE_SIZE, TILE_SIZE);
	if (!img)
		return (NULL);
	
	data = mlx_get_data_addr(img, &bpp, &size_line, &endian);
	if (!data)
	{
		mlx_destroy_image(game->mlx, img);
		return (NULL);
	}
	
	swim_phase = (frame * 0.3f);
	body_sway = (int)(sin(swim_phase) * 1.0f);
	fin_wave = (int)(sin(swim_phase + 2.0f) * 2.0f);
	shine_pos = (int)((sin(swim_phase * 0.7f) + 1.0f) * 6.0f) + 22;
	
	y = 0;
	while (y < TILE_SIZE)
	{
		x = 0;
		while (x < TILE_SIZE)
		{
			color = 0x006994;
			
			dx = x - 28;
			dy = y - (32 + body_sway);
			dist = (dx * dx) / 4 + (dy * dy);
			
			if (dist < 8 * 8 && x >= 18 && x <= 40)
			{
				if (x >= shine_pos && x <= shine_pos + 4 && abs(dy) <= 4)
					color = 0xFFE135;
				else if (abs(dy) <= 3)
					color = 0xFFD700;
				else if (abs(dy) <= 5)
					color = 0xFFC125;
				else
					color = 0xFFB000;
			}
			
			if (x >= 40 && x <= 48 + abs(fin_wave))
			{
				int tail_y = 32 + body_sway + fin_wave;
				if (abs(y - tail_y) <= 6 - (x - 40) / 2)
				{
					if (abs(y - tail_y) <= 3)
						color = 0xFFA500;
					else
						color = 0xFF8C00;
				}
				if (x >= 46 + abs(fin_wave) && abs(y - tail_y) <= 8 - (x - 40) / 2)
					color = 0xFF6347;
			}
			
			if (x >= 12 - abs(fin_wave) && x <= 18)
			{
				int nose_y = 32 + body_sway;
				if (abs(y - nose_y) <= 4 - (18 - x) / 3)
				{
					if (abs(y - nose_y) <= 2)
						color = 0xFFA500;
					else
						color = 0xFF8C00;
				}
			}
			
			if (y >= 24 + body_sway + fin_wave / 2 && y <= 28 + body_sway && x >= 24 && x <= 32)
			{
				if (abs(x - 28) <= 3)
					color = 0xFFA500;
			}
			if (y >= 36 + body_sway && y <= 40 + body_sway - fin_wave / 2 && x >= 24 && x <= 32)
			{
				if (abs(x - 28) <= 3)
					color = 0xFFA500;
			}
			
			if (x >= 20 && x <= 22 && y >= 30 + body_sway && y <= 32 + body_sway)
				color = 0x000000;
			if (x >= 21 && y >= 30 + body_sway && y <= 31 + body_sway)
				color = 0xFFFFFF;
			
			*(int *)(data + (y * size_line + x * (bpp / 8))) = color;
			x++;
		}
		y++;
	}
	
	return (img);
}

int	load_sprites(t_game *game)
{
	int	i;

	game->sprites.width = TILE_SIZE;
	game->sprites.height = TILE_SIZE;
	game->sprites.current_frame = 0;
	game->sprites.frame_count = 4;
	
	game->sprites.wall = create_coral_wall(game);
	if (!game->sprites.wall)
		return (0);
	
	game->sprites.empty = create_ocean_background(game);
	if (!game->sprites.empty)
		return (0);
	
	i = 0;
	while (i < 4)
	{
		game->sprites.collectible[i] = create_fish_sprite(game, i);
		if (!game->sprites.collectible[i])
			return (0);
		i++;
	}
	
	game->sprites.exit = create_exit_sprite(game);
	if (!game->sprites.exit)
		return (0);
	
	i = 0;
	while (i < 4)
	{
		game->sprites.player[i] = create_dolphin_sprite(game, i);
		if (!game->sprites.player[i])
			return (0);
		i++;
	}
	
	return (1);
}