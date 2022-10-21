#include "engine.h"

/*
** Use a smart trick to simulate a 2d tab with two 1d tab
** so there is only 2 mallocs instead of n*mallocs.
** This reduce access speed to the data compared to
** the classic way of a long 1d tab because it removes
** the addition and the multiplication in the index
** calculation process.
*/
t_sprite	*ft_sprite(t_engine *eng, size_t dx, size_t dy)
{
	t_sprite	*spr;
	int			tab[3];

	spr = malloc(sizeof(t_sprite));
	if (spr == NULL)
		return (NULL);
	spr->img.image = mlx_new_image(eng->mlx, dx, dy);
	if (spr->img.image == NULL)
		return (free(spr), NULL);
	spr->img.data = mlx_get_data_addr(spr->img.image, &tab[0], &tab[1], &tab[2]);
	spr->data = (t_color *)(uint32_t *)spr->img.data;
	spr->size.x = dx;
	spr->size.y = dy;
	return (spr);
}
/* PANOU */
/* PAMOA */
/* BILIMBIMBAP */
t_sprite	*ft_sprite_p(t_engine *eng, char *path)
{
	t_sprite	*spr;
	int			tab[3];

	spr = malloc(sizeof(t_sprite));
	if (spr == NULL)
		return (NULL);
	spr->img.image = mlx_xpm_file_to_image(eng->mlx,
		path, &(spr->size.x), &(spr->size.y));
	if (spr->img.image == NULL)
		return (free(spr), NULL);
	spr->img.data = mlx_get_data_addr(spr->img.image, &tab[0], &tab[1], &tab[2]);
	spr->data = (t_color *)(uint32_t *)spr->img.data;
	return (spr);
}

int	ft_destroy_sprite(t_engine *eng, t_sprite *spr)
{
	mlx_destroy_image(eng->mlx, spr->img.image);
	free(spr);
	return (1);
}

t_sprite	*ft_cpy_sprite(t_engine *eng, t_sprite *spr)
{
	t_sprite	*res;

	if (spr == NULL)
		return (NULL);
	res = ft_sprite(eng, spr->size.x, spr->size.y);
	if (res == NULL)
		return (NULL);
	ft_memcpy(res->data, spr->data, spr->size.x * spr->size.y * sizeof(t_color));
	return (res);
}
