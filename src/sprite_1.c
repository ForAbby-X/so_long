#include "engine.h"

t_color		ft_color(unsigned int d)
{
	return ((t_color){d});
}

t_sprite	*ft_sprite(size_t dx, size_t dy)
{
	t_sprite	*spr;

	spr = malloc(sizeof(t_sprite));
	if (spr == NULL)
		return (NULL);
	spr->data = malloc(dx * dy * sizeof(t_color));
	if (spr->data == NULL)
		return (free(spr), NULL);
	ft_memset(spr->data, 0, dx * dy * sizeof(t_color));
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
	ft_memcpy(spr->data, img.data, size_x * size_y * sizeof(t_color));
	mlx_destroy_image(eng->mlx, img.image);
	return (spr);
}

int	ft_destroy_sprite(t_sprite *spr)
{
	free(spr->data);
	free(spr);
	return (1);
}

int	ft_put_sprite(t_engine *eng, t_sprite *spr, int x, int y)
{
	size_t	dx;
	size_t	dy;
	size_t	index;

	dy = 0;
	while (dy < spr->size_y)
	{
		dx = 0;
		while (dx < spr->size_x)
		{
			index = dx + dy * spr->size_x;
			ft_draw(eng, x + dx, y + dy, spr->data[index]);
			dx++;
		}
		dy++;
	}
	return (1);
}
