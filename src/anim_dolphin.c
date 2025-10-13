/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_dolphin.c                                     :+:      :+:    :+:   */
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

static void	draw_dolphin_frame(char *d, int p[3], int frame)
{
	int	offset;
	int	i;
	int	j;

	offset = (frame % 2) * 2;
	p[2] = 0x6495ED;
	draw_ellipse(d, (int [4]){35 + offset, 32, 20, 11}, p);
	p[2] = 0xE0F6FF;
	draw_ellipse(d, (int [4]){33 + offset, 36, 15, 8}, p);
	i = 30 + offset;
	while (i < 40 + offset)
	{
		j = 18 + frame;
		while (j < 24 - (i - 35 - offset) * (i - 35 - offset) / 8)
			put_pix(d, i, j++, (int [3]){p[0], p[1], 0x4682B4});
		i++;
	}
	i = 52 - offset;
	while (i < 60 - offset)
	{
		j = 26 + (i - 56 + offset) * (i - 56 + offset) / 4;
		while (j < 38 - (i - 56 + offset) * (i - 56 + offset) / 4 - frame)
			put_pix(d, i, j++, (int [3]){p[0], p[1], 0x4169E1});
		i++;
	}
}

static void	draw_dolphin_eye(char *data, int p[3], int frame)
{
	int	i;
	int	j;

	i = 24 + (frame / 2);
	while (i < 28 + (frame / 2))
	{
		j = 28;
		while (j < 32)
			put_pix(data, i++, j++, (int [3]){p[0], p[1], 0x000000});
		i++;
	}
}

void	*create_dolphin_anim(void *mlx, int size, int frame)
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
	p[2] = 0x001A33;
	draw_ellipse(data, (int [4]){32, 32, 32, 32}, p);
	draw_dolphin_frame(data, p, frame);
	draw_dolphin_eye(data, p, frame);
	return (img);
}
