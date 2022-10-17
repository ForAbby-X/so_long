#include "engine.h"

t_color	ft_get_color(t_sprite *spr, t_v2i pos)
{
	if (pos.x < 0 || pos.y < 0 || (size_t)pos.x >= spr->size_x || (size_t)pos.y >= spr->size_y)
		return (ft_color_d(0));
	return (spr->data[pos.x][pos.y]);
}

int	ft_put_sprite(t_engine *eng, t_sprite *spr, t_v2i pos)
{
	t_v2i dim;

	dim.y = 0;
	while ((size_t)dim.y < spr->size_y)
	{
		dim.x = 0;
		while ((size_t)dim.x < spr->size_x)
		{
			ft_draw(eng, ft_v2iadd(pos, dim), ft_get_color(spr, dim));
			dim.x++;
		}
		dim.y++;
	}
	return (1);
}

int		ft_put_sprite_s(t_engine *eng, t_sprite *spr, t_v2i pos, int d)
{
	t_v2i dim;

	dim.y = 0;
	while ((size_t)dim.y < spr->size_y)
	{
		dim.x = 0;
		while ((size_t)dim.x < spr->size_x)
		{
			ft_rect(eng, ft_v2iadd(pos, ft_v2imul(dim, d)), ft_v2i(d, d),ft_get_color(spr, dim));
			dim.x++;
		}
		dim.y++;
	}
	return (1);
}
