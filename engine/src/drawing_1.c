/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 10:15:32 by alde-fre          #+#    #+#             */
/*   Updated: 2022/11/23 15:10:38 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

int	ft_draw(t_engine *eng, t_v2i pos, t_color color)
{
	size_t	index;

	if ((color.d >> 24) == 255 || pos.x < 0 || pos.y < 0
		|| (size_t)pos.x >= ft_eng_size_x(eng)
		|| (size_t)pos.y >= ft_eng_size_y(eng))
		return (0);
	index = pos.x + pos.y * ft_eng_size_x(eng);
	eng->sel_spr->data[index] = color;
	return (1);
}

int	ft_clear(t_engine *eng, t_color color)
{
	size_t	index;

	index = 0;
	while (index < ft_eng_size_x(eng) * ft_eng_size_y(eng))
	{
		eng->sel_spr->data[index] = color;
		index++;
	}
	return (1);
}

static void	ft_pt_circle(t_engine *eng, t_v2i pos, t_v2i dim, t_color color)
{
	ft_draw(eng, ft_v2i(pos.x + dim.x, pos.y + dim.y), color);
	ft_draw(eng, ft_v2i(pos.x - dim.x, pos.y + dim.y), color);
	ft_draw(eng, ft_v2i(pos.x + dim.x, pos.y - dim.y), color);
	ft_draw(eng, ft_v2i(pos.x - dim.x, pos.y - dim.y), color);
	ft_draw(eng, ft_v2i(pos.x + dim.y, pos.y + dim.x), color);
	ft_draw(eng, ft_v2i(pos.x - dim.y, pos.y + dim.x), color);
	ft_draw(eng, ft_v2i(pos.x + dim.y, pos.y - dim.x), color);
	ft_draw(eng, ft_v2i(pos.x - dim.y, pos.y - dim.x), color);
}

int	ft_circle(t_engine *eng, t_v2i pos, int r, t_color color)
{
	t_v2i	dim;
	int		d;

	dim.x = 0;
	dim.y = r;
	d = 3 - 2 * r;
	ft_pt_circle(eng, pos, dim, color);
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
		ft_pt_circle(eng, pos, dim, color);
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
