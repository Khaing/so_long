#include "../includes/so_long.h"

static void	draw_pixel(char *data, int x, int y, int params[3])
{
	int	color;
	int	pos;

	color = params[2];
	pos = y * params[1] + x * (params[0] / 8);
	*(int *)(data + pos) = color;
}

static void	fill_rect(char *d, int coords[4], int p[3])
{
	int	x;
	int	y;

	y = coords[1] - 1;
	while (++y < coords[3])
	{
		x = coords[0] - 1;
		while (++x < coords[2])
			draw_pixel(d, x, y, p);
	}
}

void	*create_ocean(void *mlx, int size)
{
	void	*img;
	char	*data;
	int		p[3];
	int		coords[4];

	img = mlx_new_image(mlx, size, size);
	if (!img)
		return (NULL);
	data = mlx_get_data_addr(img, &p[0], &p[1], &p[2]);
	if (!data)
		return (mlx_destroy_image(mlx, img), NULL);
	coords[0] = 0;
	coords[1] = 0;
	coords[2] = size;
	coords[3] = size;
	p[2] = 0x4A90E2;
	fill_rect(data, coords, p);
	return (img);
}

static void	draw_circle(char *d, int center[2], int r, int p[3])
{
	int	x;
	int	y;
	int	dx;
	int	dy;

	y = center[1] - r - 1;
	while (++y <= center[1] + r)
	{
		x = center[0] - r - 1;
		while (++x <= center[0] + r)
		{
			dx = x - center[0];
			dy = y - center[1];
			if (dx * dx + dy * dy <= r * r)
				draw_pixel(d, x, y, p);
		}
	}
}

static void	*create_dolphin_body(void *mlx, int size, char *data, int p[3])
{
	int	center[2];
	int	coords[4];

	center[0] = size / 2;
	center[1] = size / 2;
	p[2] = 0x5DADE2;
	draw_circle(data, center, size / 3, p);
	coords[0] = size / 4;
	coords[1] = size / 3;
	coords[2] = size * 3 / 4;
	coords[3] = size * 2 / 3;
	p[2] = 0x87CEEB;
	fill_rect(data, coords, p);
	coords[0] = size / 3;
	coords[1] = size / 4;
	coords[2] = size / 3 + 4;
	coords[3] = size / 4 + 4;
	p[2] = 0x000000;
	fill_rect(data, coords, p);
	return (mlx_new_image(mlx, size, size));
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
	p[2] = 0x4A90E2;
	fill_rect(data, (int[4]){0, 0, size, size}, p);
	create_dolphin_body(mlx, size, data, p);
	return (img);
}

void	*create_fish(void *mlx, int size)
{
	void	*img;
	char	*data;
	int		p[3];
	int		center[2];
	int		coords[4];

	img = mlx_new_image(mlx, size, size);
	if (!img)
		return (NULL);
	data = mlx_get_data_addr(img, &p[0], &p[1], &p[2]);
	if (!data)
		return (mlx_destroy_image(mlx, img), NULL);
	p[2] = 0x4A90E2;
	fill_rect(data, (int[4]){0, 0, size, size}, p);
	center[0] = size / 2;
	center[1] = size / 2;
	p[2] = 0xFFD700;
	draw_circle(data, center, size / 4, p);
	coords[0] = size / 2 - 2;
	coords[1] = size / 2 - 2;
	coords[2] = size / 2 + 2;
	coords[3] = size / 2 + 2;
	p[2] = 0x000000;
	fill_rect(data, coords, p);
	return (img);
}

void	*create_exit_gate(void *mlx, int size)
{
	void	*img;
	char	*data;
	int		p[3];
	int		coords[4];
	int		i;

	img = mlx_new_image(mlx, size, size);
	if (!img)
		return (NULL);
	data = mlx_get_data_addr(img, &p[0], &p[1], &p[2]);
	if (!data)
		return (mlx_destroy_image(mlx, img), NULL);
	p[2] = 0x4A90E2;
	fill_rect(data, (int[4]){0, 0, size, size}, p);
	p[2] = 0x228B22;
	i = -1;
	while (++i < 4)
	{
		coords[0] = size / 8 + i * size / 4;
		coords[1] = size / 4;
		coords[2] = coords[0] + size / 8;
		coords[3] = size * 3 / 4;
		fill_rect(data, coords, p);
	}
	return (img);
}

void	*create_coral(void *mlx, int size)
{
	void	*img;
	char	*data;
	int		p[3];
	int		center[2];
	int		i;

	img = mlx_new_image(mlx, size, size);
	if (!img)
		return (NULL);
	data = mlx_get_data_addr(img, &p[0], &p[1], &p[2]);
	if (!data)
		return (mlx_destroy_image(mlx, img), NULL);
	p[2] = 0xFF6347;
	fill_rect(data, (int[4]){0, 0, size, size}, p);
	i = -1;
	while (++i < 3)
	{
		center[0] = size / 4 + i * size / 4;
		center[1] = size / 4 + i * size / 6;
		p[2] = 0xFF4500 - i * 0x000500;
		draw_circle(data, center, size / 6, p);
	}
	return (img);
}
