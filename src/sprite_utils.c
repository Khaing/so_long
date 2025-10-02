#include "../includes/so_long.h"

static void	fill_pixel(char *data, int pos, int color)
{
	*(int *)(data + pos) = color;
}

void	*create_colored_square(void *mlx, int size, int color)
{
	void	*img;
	char	*data;
	int		params[3];
	int		coords[2];

	img = mlx_new_image(mlx, size, size);
	if (!img)
		return (NULL);
	data = mlx_get_data_addr(img, &params[0], &params[1], &params[2]);
	if (!data)
	{
		mlx_destroy_image(mlx, img);
		return (NULL);
	}
	coords[1] = -1;
	while (++coords[1] < size)
	{
		coords[0] = -1;
		while (++coords[0] < size)
			fill_pixel(data, coords[1] * params[1]
				+ coords[0] * (params[0] / 8), color);
	}
	return (img);
}
