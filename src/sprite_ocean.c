/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_ocean.c                                     :+:      :+:    :+:   */
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
