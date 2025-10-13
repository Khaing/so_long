/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmar <kmar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 00:00:00 by kmar              #+#    #+#             */
/*   Updated: 2025/10/08 00:00:00 by kmar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	put_pix(char *d, int x, int y, int p[3])
{
	if (x >= 0 && x < 64 && y >= 0 && y < 64)
		*(int *)(d + y * p[1] + x * (p[0] / 8)) = p[2];
}

static int	get_gate_color(int i, int j)
{
	int	dist_sq;
	int	color;

	dist_sq = (i - 32) * (i - 32) + (j - 32) * (j - 32);
	color = 0x001A33;
	if (dist_sq < 484)
		color = 0x00CED1 - dist_sq * 200;
	if (dist_sq < 196)
		color = 0x40E0D0 + ((i + j) % 4) * 0x101010;
	return (color);
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
			p[2] = get_gate_color(i, j);
			put_pix(data, i, j++, p);
		}
		i++;
	}
	return (img);
}

static int	get_coral_color(int i, int j)
{
	int	color;

	color = 0x0D4D0D + (i % 12) * 0x000500;
	if (i % 16 < 6 && j > 10 && j < 54)
		color = 0x228B22;
	if ((i % 16) % 3 == 0 && j > 8 && j < 56)
		color = 0x3CB371;
	return (color);
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
			p[2] = get_coral_color(i, j);
			put_pix(data, i, j++, p);
		}
		i++;
	}
	return (img);
}
