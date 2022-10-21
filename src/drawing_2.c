#include "engine.h"

t_color	ft_get_color(t_sprite *spr, t_v2i pos)
{
	t_color	col;
	size_t	index;

	if (pos.x < 0 || pos.y < 0 || pos.x >= spr->size.x || pos.y >= spr->size.y)
		return (ft_color_d(0));
	index = pos.y * spr->size.x + pos.x;
	col = spr->data[index];
	return (col);
}

int	ft_put_sprite(t_engine *eng, t_sprite *spr, t_v2i pos)
{
	t_v2i dim;

	dim.y = 0;
	while (dim.y < spr->size.y)
	{
		dim.x = 0;
		while (dim.x < spr->size.x)
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
	while (dim.y < spr->size.y)
	{
		dim.x = 0;
		while (dim.x < spr->size.x)
		{
			ft_rect(eng, ft_v2iadd(pos, ft_v2imul(dim, d)), ft_v2i(d, d),ft_get_color(spr, dim));
			dim.x++;
		}
		dim.y++;
	}
	return (1);
}

int		ft_put_sprite_r(t_engine *eng, t_sprite *spr,
			t_v2i pos, t_v2i cen, float rot)
{
	t_v2i dim;
	t_v2i read;
	
	dim.y = -spr->size.y;
	while (dim.y < spr->size.y * 2)
	{
		dim.x = -spr->size.x;
		while (dim.x < spr->size.x * 2)
		{
			read.x = cen.x + cosf(-rot) * dim.x + sinf(-rot) * dim.y;
			read.y = cen.y - sinf(-rot) * dim.x + cosf(-rot) * dim.y;
			ft_draw(eng, ft_v2iadd(pos, dim), ft_get_color(spr, read));
			dim.x++;
		}
		dim.y++;
	}
	return (1);
}
