#include "engine.h"

/*
** Use a smart trick to simulate a 2d tab with two 1d tab
** so there is only 2 mallocs instead of n*mallocs.
** This reduce access speed to the data compared to
** the classic way of a long 1d tab because it removes
** the addition and the multiplication in the index
** calculation process.
*/
t_sprite	*ft_sprite(size_t dx, size_t dy)
{
	t_sprite	*spr;
	size_t		i;

	spr = malloc(sizeof(t_sprite));
	if (spr == NULL)
		return (NULL);
	spr->data = malloc(dy * sizeof(t_color *));
	if (spr->data == NULL)
		return (free(spr), NULL);
	spr->data[0] = malloc(dx * dy * sizeof(t_color));
	if (spr->data[0] == NULL)
		return (free(spr->data), free(spr), NULL);
	ft_memset(spr->data[0], 0, dx * dy * sizeof(t_color));
	i = -1;
	while (++i < dy)
		spr->data[i] = spr->data[0] + dx * i;
	spr->size_x = dx;
	spr->size_y = dy;
	return (spr);
}

t_sprite	*ft_sprite_p(t_engine *eng, char *path)
{
	int			size_x;
	int			size_y;
	t_img		img;
	t_sprite	*spr;

	img.image = mlx_xpm_file_to_image(eng->mlx, path, &size_x, &size_y);
	if (img.image == NULL)
		return ((t_sprite *) 0);
	img.data = mlx_get_data_addr(img.image, &img.bpp,
			&img.size_line, &img.format);
	spr = ft_sprite(size_x, size_y);
	if (spr == NULL)
		return (mlx_destroy_image(eng->mlx, img.image), NULL);
	ft_memcpy(spr->data[0], img.data, size_x * size_y * sizeof(t_color));
	mlx_destroy_image(eng->mlx, img.image);
	return (spr);
}

int	ft_destroy_sprite(t_sprite *spr)
{
	free(spr->data[0]);
	free(spr->data);
	free(spr);
	return (1);
}

t_sprite	*ft_cpy_sprite(t_sprite *spr)
{
	t_sprite	*res;

	if (spr == NULL)
		return (NULL);
	res = ft_sprite(spr->size_x, spr->size_y);
	if (res == NULL)
		return (NULL);
	ft_memcpy(res->data[0], spr->data[0], spr->size_x * spr->size_y * sizeof(t_color));
	return (res);
}
