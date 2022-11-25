/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 10:15:25 by alde-fre          #+#    #+#             */
/*   Updated: 2022/11/25 08:18:15 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

t_color	ft_get_color(t_sprite *spr, t_v2i pos)
{
	size_t	index;

	if (pos.x < 0 || pos.y < 0 || pos.x >= spr->size.x || pos.y >= spr->size.y)
		return (ft_color_d(0xFF000000));
	index = pos.y * spr->size.x + pos.x;
	return (spr->data[index]);
}

int	ft_put_sprite(t_engine *eng, t_sprite *spr, t_v2i pos)
{
	t_v2i	dim;

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

int	ft_put_sprite_s(t_engine *eng, t_sprite *spr, t_v2i pos, int d)
{
	t_v2i	dim;

	dim.y = 0;
	while (dim.y < spr->size.y)
	{
		dim.x = 0;
		while (dim.x < spr->size.x)
		{
			ft_rect(eng, ft_v2iadd(pos, ft_v2imul(dim, d)), ft_v2i(d, d),
				ft_get_color(spr, dim));
			dim.x++;
		}
		dim.y++;
	}
	return (1);
}

void	_ft_get_border(t_sprite *spr,
	t_v2i cen, float rot, t_v2i	out[2])
{
	t_v2i	cor[4];
	int		n;

	cor[0] = ft_v2irot(ft_v2i(-cen.x, -cen.y), rot);
	cor[1] = ft_v2irot(ft_v2i(-cen.x, spr->size.y - cen.y), rot);
	cor[2] = ft_v2irot(ft_v2i(spr->size.x - cen.x, -cen.y), rot);
	cor[3] = ft_v2irot(ft_v2isub(spr->size, cen), rot);
	out[0] = cor[0];
	out[1] = cor[0];
	n = 1;
	while (n < 4)
	{
		out[0].x = ft_min(out[0].x, cor[n].x);
		out[0].y = ft_min(out[0].y, cor[n].y);
		out[1].x = ft_max(out[1].x, cor[n].x);
		out[1].y = ft_max(out[1].y, cor[n].y);
		n++;
	}
}

int	ft_put_sprite_r(t_engine *eng, t_sprite *spr,
			t_v2i pos, t_v2i cen, float rot)
{
	t_v2i	dim;
	t_v2i	read;
	t_v2i	bord[2];

	_ft_get_border(spr, cen, rot, bord);
	dim.y = bord[0].y;
	while (dim.y <= bord[1].y)
	{
		dim.x = bord[0].x;
		while (dim.x <= bord[1].x)
		{
			read.x = floor(cen.x + cosf(rot) * dim.x + sinf(rot) * dim.y);
			read.y = floor(cen.y - sinf(rot) * dim.x + cosf(rot) * dim.y);
			ft_draw(eng, ft_v2iadd(pos, dim), ft_get_color(spr, read));
			dim.x++;
		}
		dim.y++;
	}
	return (1);
}
