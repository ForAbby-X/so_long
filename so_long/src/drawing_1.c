#include "engine.h"

int	ft_draw(t_engine *eng, int x, int y, t_color color)
{
	size_t	index;

	if (color.a == 0 || x < 0 || y < 0 || (size_t)x > eng->win_x || (size_t)y > eng->win_y)
		return (0);
	index = y * eng->img.size_line / 4 + x * (eng->img.bpp / 8) / 4;
	((int *)eng->img.data)[index] = color.d;
	return (1);
}

int	ft_clear(t_engine *eng, t_color color)
{
	size_t	x;
	size_t	y;
	size_t	index;

	y = 0;
	while (y < eng->win_y)
	{
		x = 0;
		while (x < eng->win_x)
		{
			index = y * eng->img.size_line / 4 + x * (eng->img.bpp / 8) / 4;
			((int *)eng->img.data)[index] = color.d;
			x++;
		}
		y++;
	}
	return (1);
}

static void	ft_pt_circle(t_engine *eng, int x, int y, int dx, int dy, t_color color)
{
	ft_draw(eng, x+dx, y+dy, color);
	ft_draw(eng, x-dx, y+dy, color);
	ft_draw(eng, x+dx, y-dy, color);
	ft_draw(eng, x-dx, y-dy, color);
	ft_draw(eng, x+dy, y+dx, color);
	ft_draw(eng, x-dy, y+dx, color);
	ft_draw(eng, x+dy, y-dx, color);
	ft_draw(eng, x-dy, y-dx, color);
}

int	ft_circle(t_engine *eng, int x, int y, int r, t_color color)
{
	int	dx;
	int	dy;
	int	d;

	dx = 0;
	dy = r;
	d = 3 - 2 * r;
	ft_pt_circle(eng, x, y, dx, dy, color);
	while (dy >= dx)
	{
		dx++;
		if (d > 0)
		{
			dy--;
			d = d + 4 * (dx - dy) + 10;
		}
		else
			d = d + 4 * dx + 6;
		ft_pt_circle(eng, x, y, dx, dy, color);
	}
	return (1);
}
