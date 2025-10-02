#include "../includes/so_long.h"

static void	put_pix(char *d, int x, int y, int p[3])
{
	if (x >= 0 && x < 64 && y >= 0 && y < 64)
		*(int *)(d + y * p[1] + x * (p[0] / 8)) = p[2];
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
				put_pix(d, x, y, p);
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
			p[2] = 0x001A33 + (y * 0x002244 / size);
			if ((x + y * 3) % 16 < 2)
				p[2] += 0x001122;
			put_pix(data, x, y, p);
		}
	}
	return (img);
}

static void	draw_dolphin_body(char *d, int p[3])
{
	p[2] = 0x6495ED;
	draw_ellipse(d, (int[4]){35, 32, 20, 11}, p);
	p[2] = 0xE0F6FF;
	draw_ellipse(d, (int[4]){33, 36, 15, 8}, p);
}

static void	draw_dolphin_fins(char *d, int p[3])
{
	int	i;
	int	j;

	i = 30;
	while (i < 40)
	{
		j = 18;
		while (j < 24 - (i - 35) * (i - 35) / 8)
			put_pix(d, i, j++, (int[3]){p[0], p[1], 0x4682B4});
		i++;
	}
	i = 52;
	while (i < 60)
	{
		j = 26 + (i - 56) * (i - 56) / 4;
		while (j < 38 - (i - 56) * (i - 56) / 4)
			put_pix(d, i, j++, (int[3]){p[0], p[1], 0x4169E1});
		i++;
	}
}

void	*create_dolphin(void *mlx, int size)
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
	p[2] = 0x001A33;
	draw_ellipse(data, (int[4]){32, 32, 32, 32}, p);
	draw_dolphin_body(data, p);
	draw_dolphin_fins(data, p);
	i = 24;
	while (i < 28)
	{
		j = 28;
		while (j < 32)
			put_pix(data, i++, j++, (int[3]){p[0], p[1], 0x000000});
		i++;
	}
	return (img);
}

static void	draw_fish_stripes(char *d, int p[3])
{
	int	i;
	int	j;

	i = 26;
	while (i < 30)
	{
		j = 25;
		while (j < 39)
			put_pix(d, i, j++, (int[3]){p[0], p[1], 0xFFFFFF});
		i++;
	}
	i = 34;
	while (i < 38)
	{
		j = 25;
		while (j < 39)
			put_pix(d, i, j++, (int[3]){p[0], p[1], 0xFFFFFF});
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
	p[2] = 0x001A33;
	draw_ellipse(data, (int[4]){32, 32, 32, 32}, p);
	p[2] = 0xFF8C00;
	draw_ellipse(data, (int[4]){30, 32, 13, 10}, p);
	draw_fish_stripes(data, p);
	i = 43;
	while (i < 52)
	{
		j = 27 + (i - 47) * (i - 47) / 5;
		while (j < 37 - (i - 47) * (i - 47) / 5)
			put_pix(data, i, j++, (int[3]){p[0], p[1], 0xFFAA33});
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
	i = 0;
	while (i < 64)
	{
		j = 0;
		while (j < 64)
		{
			p[2] = 0x001A33;
			if (((i - 32) * (i - 32) + (j - 32) * (j - 32)) < 484)
				p[2] = 0x00CED1 - ((i - 32) * (i - 32)
						+ (j - 32) * (j - 32)) * 200;
			if (((i - 32) * (i - 32) + (j - 32) * (j - 32)) < 196)
				p[2] = 0x40E0D0 + ((i + j) % 4) * 0x101010;
			put_pix(data, i, j++, p);
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
	int		j;

	img = mlx_new_image(mlx, size, size);
	if (!img)
		return (NULL);
	data = mlx_get_data_addr(img, &p[0], &p[1], &p[2]);
	if (!data)
		return (mlx_destroy_image(mlx, img), NULL);
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			p[2] = 0x0D4D0D + (i % 12) * 0x000500;
			if (i % 16 < 6 && j > 10 && j < 54)
				p[2] = 0x228B22;
			if ((i % 16) % 3 == 0 && j > 8 && j < 56)
				p[2] = 0x3CB371;
			put_pix(data, i, j++, p);
		}
		i++;
	}
	return (img);
}
