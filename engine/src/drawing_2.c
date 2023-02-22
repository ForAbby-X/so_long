/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 10:15:25 by alde-fre          #+#    #+#             */
/*   Updated: 2023/02/04 16:27:16 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

t_color	ft_get_color(t_sprite *spr, t_v2i pos)
{
	size_t	index;

	if (pos[0] < 0 || pos[1] < 0
		|| pos[0] >= spr->size[0] || pos[1] >= spr->size[1])
		return ((t_color)(0xFF000000));
	index = pos[1] * spr->size[0] + pos[0];
	return (spr->data[index]);
}

void	ft_put_sprite(t_engine *eng, t_sprite *spr, t_v2i pos)
{
	t_v2i	dim;

	dim[1] = 0;
	while (dim[1] < spr->size[1])
	{
		dim[0] = 0;
		while (dim[0] < spr->size[0])
		{
			ft_draw(eng, pos + dim, ft_get_color(spr, dim));
			dim[0]++;
		}
		dim[1]++;
	}
}

void	ft_put_sprite_s(t_engine *eng, t_sprite *spr, t_v2i pos, int d)
{
	t_v2i	dim;

	dim[1] = 0;
	while (dim[1] < spr->size[1])
	{
		dim[0] = 0;
		while (dim[0] < spr->size[0])
		{
			ft_rect(eng, pos + dim * d, (t_v2i){d, d},
				ft_get_color(spr, dim));
			dim[0]++;
		}
		dim[1]++;
	}
}

void	ft_get_border(t_sprite *spr,
	t_v2i cen, float rot, t_v2i	out[2])
{
	t_v2i	cor[4];
	int		n;

	cor[0] = ft_v2irot((t_v2i){-cen[0], -cen[1]}, rot);
	cor[1] = ft_v2irot((t_v2i){-cen[0], spr->size[1] - cen[1]}, rot);
	cor[2] = ft_v2irot((t_v2i){spr->size[0] - cen[0], -cen[1]}, rot);
	cor[3] = ft_v2irot(spr->size - cen, rot);
	out[0] = cor[0];
	out[1] = cor[0];
	n = 1;
	while (n < 4)
	{
		out[0][0] = ft_min(out[0][0], cor[n][0]);
		out[0][1] = ft_min(out[0][1], cor[n][1]);
		out[1][0] = ft_max(out[1][0], cor[n][0]);
		out[1][1] = ft_max(out[1][1], cor[n][1]);
		n++;
	}
}

void	ft_put_sprite_r(t_engine *eng, t_sprite *spr,
			t_rect i, float rot)
{
	t_v2i	dim;
	t_v2i	read;
	t_v2i	bord[2];
	t_v2f	sc;

	ft_get_border(spr, i.dim, rot, bord);
	sc = (t_v2f){sinf(rot), cosf(rot)};
	dim[1] = bord[0][1];
	while (dim[1] <= bord[1][1])
	{
		dim[0] = bord[0][0];
		while (dim[0] <= bord[1][0])
		{
			read[0] = floorl(i.dim[0] + sc[1] * dim[0] + sc[0] * dim[1]);
			read[1] = floorl(i.dim[1] - sc[0] * dim[0] + sc[1] * dim[1]);
			ft_draw(eng, i.pos + dim, ft_get_color(spr, read));
			dim[0]++;
		}
		dim[1]++;
	}
}
