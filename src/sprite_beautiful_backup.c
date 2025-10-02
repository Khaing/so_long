#include "../includes/so_long.h"

static void	put_pixel(char *data, int x, int y, int params[3])
{
	int	pos;

	if (x >= 0 && x < 64 && y >= 0 && y < 64)
	{
		pos = y * params[1] + x * (params[0] / 8);
		*(int *)(data + pos) = params[2];
	}
}

static void	draw_ellipse(char *d, int c[4], int p[3])
{
	int	x;
	int	y;
	int	dx;
	int	dy;

	y = c[1] - c[3] - 1;
	while (++y <= c[1] + c[3])
	{
		x = c[0] - c[2] - 1;
		while (++x <= c[0] + c[2])
		{
			dx = x - c[0];
			dy = y - c[1];
			if ((dx * dx * c[3] * c[3] + dy * dy * c[2] * c[2])
				<= (c[2] * c[2] * c[3] * c[3]))
				put_pixel(d, x, y, p);
		}
	}
}

void	*create_ocean(void *mlx, int size)
{
	void	*img;
	char	*data;
	int		p[3];
	int		y;
	int		x;

	img = mlx_new_image(mlx, size, size);
	if (!img)
		return (NULL);
	data = mlx_get_data_addr(img, &p[0], &p[1], &p[2]);
	if (!data)
		return (mlx_destroy_image(mlx, img), NULL);
	y = -1;
	while (++y < size)
	{
		x = -1;
		while (++x < size)
		{
			p[2] = 0x1E90FF + ((y / 8) % 2) * 0x001020;
			put_pixel(data, x, y, p);
		}
	}
	return (img);
}

static void	draw_dolphin_body(char *d, int p[3])
{
	int	parts[4];

	parts[0] = 40;
	parts[1] = 32;
	parts[2] = 18;
	parts[3] = 12;
	p[2] = 0x4169E1;
	draw_ellipse(d, parts, p);
	parts[0] = 38;
	parts[1] = 36;
	parts[2] = 14;
	parts[3] = 9;
	p[2] = 0x87CEEB;
	draw_ellipse(d, parts, p);
}

static void	draw_dolphin_details(char *d, int p[3])
{
	int	i;
	int	j;
	int	parts[4];

	i = 22;
	while (i < 26)
	{
		j = 30;
		while (j < 34)
			put_pixel(d, i++, j++, (int[3]){p[0], p[1], 0x000000});
		i++;
	}
	parts[0] = 58;
	parts[1] = 28;
	parts[2] = 6;
	parts[3] = 8;
	p[2] = 0x4169E1;
	draw_ellipse(d, parts, p);
	parts[0] = 32;
	parts[1] = 20;
	parts[2] = 8;
	parts[3] = 4;
	draw_ellipse(d, parts, p);
}

void	*create_dolphin(void *mlx, int size)
{
	void	*img;
	char	*data;
	int		p[3];

	img = mlx_new_image(mlx, size, size);
	if (!img)
		return (NULL);
	data = mlx_get_data_addr(img, &p[0], &p[1], &p[2]);
	if (!data)
		return (mlx_destroy_image(mlx, img), NULL);
	p[2] = 0x1E90FF;
	draw_ellipse(data, (int[4]){32, 32, 32, 32}, p);
	draw_dolphin_body(data, p);
	draw_dolphin_details(data, p);
	return (img);
}

static void	draw_fish_body(char *d, int p[3])
{
	int	parts[4];

	parts[0] = 32;
	parts[1] = 32;
	parts[2] = 14;
	parts[3] = 10;
	p[2] = 0xFFD700;
	draw_ellipse(d, parts, p);
	parts[0] = 30;
	parts[1] = 32;
	parts[2] = 10;
	parts[3] = 7;
	p[2] = 0xFFA500;
	draw_ellipse(d, parts, p);
}

static void	draw_fish_details(char *d, int p[3])
{
	int	i;
	int	j;

	i = 24;
	while (i < 28)
	{
		j = 28;
		while (j < 32)
			put_pixel(d, i++, j++, (int[3]){p[0], p[1], 0x000000});
		i++;
	}
	i = 46;
	while (i < 54)
	{
		j = 26 + (i - 50) * (i - 50) / 4;
		while (j < 38 - (i - 50) * (i - 50) / 4)
			put_pixel(d, i, j++, (int[3]){p[0], p[1], 0xFFD700});
		i++;
	}
}

void	*create_fish(void *mlx, int size)
{
	void	*img;
	char	*data;
	int		p[3];
	int		i;
	int		j;

	img = mlx_new_image(mlx, size, size);
	if (!img)
		return (NULL);
	data = mlx_get_data_addr(img, &p[0], &p[1], &p[2]);
	if (!data)
		return (mlx_destroy_image(mlx, img), NULL);
	p[2] = 0x1E90FF;
	draw_ellipse(data, (int[4]){32, 32, 32, 32}, p);
	draw_fish_body(data, p);
	draw_fish_details(data, p);
	i = 32;
	while (i < 42)
	{
		j = 18 + (i - 37) * (i - 37) / 3;
		while (j < 46 - (i - 37) * (i - 37) / 3)
			put_pixel(data, i, j++, (int[3]){p[0], p[1], 0xFFA500});
		i++;
	}
	return (img);
}

void	*create_exit_gate(void *mlx, int size)
{
	void	*img;
	char	*data;
	int		p[3];
	int		i;
	int		j;

	img = mlx_new_image(mlx, size, size);
	if (!img)
		return (NULL);
	data = mlx_get_data_addr(img, &p[0], &p[1], &p[2]);
	if (!data)
		return (mlx_destroy_image(mlx, img), NULL);
	p[2] = 0x1E90FF;
	draw_ellipse(data, (int[4]){32, 32, 32, 32}, p);
	i = 0;
	while (i < 4)
	{
		j = 12;
		while (j < 52)
		{
			put_pixel(data, 12 + i * 13, j, (int[3]){p[0], p[1], 0x228B22});
			put_pixel(data, 13 + i * 13, j, (int[3]){p[0], p[1], 0x228B22});
			put_pixel(data, 14 + i * 13, j++, (int[3]){p[0], p[1], 0x32CD32});
		}
		i++;
	}
	return (img);
}

void	*create_coral(void *mlx, int size)
{
	void	*img;
	char	*data;
	int		p[3];
	int		i;

	img = mlx_new_image(mlx, size, size);
	if (!img)
		return (NULL);
	data = mlx_get_data_addr(img, &p[0], &p[1], &p[2]);
	if (!data)
		return (mlx_destroy_image(mlx, img), NULL);
	p[2] = 0xFF6347;
	draw_ellipse(data, (int[4]){32, 32, 32, 32}, p);
	i = 0;
	while (i < 5)
	{
		p[2] = 0xFF4500 - i * 0x000A00;
		draw_ellipse(data, (int[4]){16 + i * 8, 20 + i * 6, 8, 8}, p);
		draw_ellipse(data, (int[4]){48 - i * 8, 20 + i * 6, 8, 8}, p);
		draw_ellipse(data, (int[4]){32, 44 - i * 4, 10, 10}, p);
		i++;
	}
	return (img);
}
