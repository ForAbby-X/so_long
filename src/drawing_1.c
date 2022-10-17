#include "engine.h"

int	ft_draw(t_engine *eng, t_v2i pos, t_color color)
{
	size_t	index;

	if (color.a == 0 || pos.x < 0 || pos.y < 0 || (size_t)pos.x >= eng->win_x || (size_t)pos.y >= eng->win_y)
		return (0);
	index = pos.y * eng->img.size_line + pos.x * (eng->img.bpp >> 3);
	((int *)eng->img.data)[index >> 2] = color.d;
	return (1);
}

int	ft_clear(t_engine *eng, t_color color)
{
	t_v2i	pos;
	size_t	index;

	pos.y = 0;
	while ((size_t)pos.y < eng->win_y)
	{
		pos.x = 0;
		while ((size_t)pos.x < eng->win_x)
		{
			index = pos.y * eng->img.size_line + pos.x * (eng->img.bpp >> 3);
			((int *)eng->img.data)[index >> 2] = color.d;
			pos.x++;
		}
		pos.y++;
	}
	return (1);
}

static void	ft_pt_circle(t_engine *eng, int x, int y, int dx, int dy, t_color color)
{
	ft_draw(eng, ft_v2i(x+dx, y+dy), color);
	ft_draw(eng, ft_v2i(x-dx, y+dy), color);
	ft_draw(eng, ft_v2i(x+dx, y-dy), color);
	ft_draw(eng, ft_v2i(x-dx, y-dy), color);
	ft_draw(eng, ft_v2i(x+dy, y+dx), color);
	ft_draw(eng, ft_v2i(x-dy, y+dx), color);
	ft_draw(eng, ft_v2i(x+dy, y-dx), color);
	ft_draw(eng, ft_v2i(x-dy, y-dx), color);
}

int	ft_circle(t_engine *eng, t_v2i pos, int r, t_color color)
{
	t_v2i	dim;
	int		d;

	dim.x = 0;
	dim.y = r;
	d = 3 - 2 * r;
	ft_pt_circle(eng, pos.x, pos.y, dim.x, dim.y, color);
	while (dim.y >= dim.x)
	{
		dim.x++;
		if (d > 0)
		{
			dim.y--;
			d = d + 4 * (dim.x - dim.y) + 10;
		}
		else
			d = d + 4 * dim.x + 6;
		ft_pt_circle(eng, pos.x, pos.y, dim.x, dim.y, color);
	}
	return (1);
}

int	ft_rect(t_engine *eng, t_v2i pos, t_v2i dim, t_color color)
{
	t_v2i	p;

	p.y = 0;
	while (p.y < dim.y)
	{
		p.x = 0;
		while (p.x < dim.x)
		{
			ft_draw(eng, ft_v2iadd(pos, p), color);
			p.x++;
		}
		p.y++;
	}
	return (1);
}

