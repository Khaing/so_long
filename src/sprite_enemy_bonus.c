/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_enemy_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmar <kmar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 00:00:00 by kmar              #+#    #+#             */
/*   Updated: 2025/10/13 00:00:00 by kmar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

static void	put_pixel(char *data, int x, int y, int p[3])
{
	if (x >= 0 && x < 64 && y >= 0 && y < 64)
		*(int *)(data + y * p[1] + x * (p[0] / 8)) = p[2];
}

static void	draw_enemy_body(char *data, int p[3], int frame)
{
	int	i;
	int	j;
	int	offset;

	offset = (frame % 2) * 2;
	i = 20;
	while (i < 44)
	{
		j = 20 + offset;
		while (j < 44 + offset)
		{
			if ((i - 32) * (i - 32) + (j - 32 - offset) * (j - 32 - offset)
				< 144)
			{
				p[2] = 0xFF0000;
				put_pixel(data, i, j, p);
			}
			j++;
		}
		i++;
	}
}

static void	draw_enemy_eyes(char *data, int p[3])
{
	int	i;
	int	j;

	i = 26;
	while (i < 30)
	{
		j = 28;
		while (j < 32)
		{
			p[2] = 0xFFFFFF;
			put_pixel(data, i, j, p);
			put_pixel(data, i + 8, j, p);
			j++;
		}
		i++;
	}
	p[2] = 0x000000;
	put_pixel(data, 28, 30, p);
	put_pixel(data, 36, 30, p);
}

void	*create_enemy_sprite(void *mlx, int size, int frame)
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
	draw_enemy_body(data, p, frame);
	draw_enemy_eyes(data, p);
	return (img);
}
