/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:41:05 by alde-fre          #+#    #+#             */
/*   Updated: 2022/11/25 02:58:51 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

int	ft_draw_solid(t_engine *eng, t_v2i pos, t_color color)
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

int	ft_put_sprite_part(t_engine *eng, t_sprite *spr, t_v2i pos, t_rect rect)
{
	t_v2i	dim;

	dim.y = 0;
	while (dim.y < rect.dim.y)
	{
		dim.x = 0;
		while (dim.x < rect.dim.x)
		{
			ft_draw(eng, ft_v2iadd(pos, dim),
				ft_get_color(spr, ft_v2iadd(rect.pos, dim)));
			dim.x++;
		}
		dim.y++;
	}
	return (1);
}

int	ft_put_sprite_solid(t_engine *eng, t_sprite *spr, t_v2i pos)
{
	t_v2i	dim;

	dim.y = 0;
	while (dim.y < spr->size.y)
	{
		dim.x = 0;
		while (dim.x < spr->size.x)
		{
			ft_draw_solid(eng, ft_v2iadd(pos, dim), ft_get_color(spr, dim));
			dim.x++;
		}
		dim.y++;
	}
	return (1);
}
