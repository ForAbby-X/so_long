/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:41:05 by alde-fre          #+#    #+#             */
/*   Updated: 2022/12/23 18:46:53 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

int	ft_draw_solid(t_engine *eng, t_v2i pos, t_color color)
{
	size_t	index;

	if ((color.d >> 24) == 255 || pos[0] < 0 || pos[1] < 0
		|| (size_t)pos[0] >= ft_eng_size_x(eng)
		|| (size_t)pos[1] >= ft_eng_size_y(eng))
		return (0);
	index = pos[0] + pos[1] * ft_eng_size_x(eng);
	eng->sel_spr->data[index] = color;
	return (1);
}

int	ft_put_sprite_part(t_engine *eng, t_sprite *spr, t_v2i pos, t_rect rect)
{
	t_v2i	dim;

	dim[1] = 0;
	while (dim[1] < rect.dim[1])
	{
		dim[0] = 0;
		while (dim[0] < rect.dim[0])
		{
			ft_draw(eng, ft_v2iadd(pos, dim),
				ft_get_color(spr, ft_v2iadd(rect.pos, dim)));
			dim[0]++;
		}
		dim[1]++;
	}
	return (1);
}

int	ft_put_sprite_part_s(t_engine *eng, t_sprite *spr,
		t_v2i pos, t_rect_s rect_t)
{
	t_v2i	dim;

	dim[1] = 0;
	while (dim[1] < rect_t.dim[1])
	{
		dim[0] = 0;
		while (dim[0] < rect_t.dim[0])
		{
			ft_rect(eng, ft_v2iadd(pos, ft_v2imul(dim, rect_t.size)),
				(t_v2i){rect_t.size, rect_t.size},
				ft_get_color(spr, ft_v2iadd(rect_t.pos,
						dim)));
			dim[0]++;
		}
		dim[1]++;
	}
	return (1);
}

int	ft_put_sprite_solid(t_engine *eng, t_sprite *spr, t_v2i pos)
{
	t_v2i	dim;

	dim[1] = 0;
	while (dim[1] < spr->size[1])
	{
		dim[0] = 0;
		while (dim[0] < spr->size[0])
		{
			ft_draw_solid(eng, ft_v2iadd(pos, dim), ft_get_color(spr, dim));
			dim[0]++;
		}
		dim[1]++;
	}
	return (1);
}

void	ft_put_text(t_engine *eng, t_v2i pos, char *str, t_length size)
{
	t_length	i;
	char		c;

	i = 0;
	while (str[i])
	{
		c = str[i] - '!';
		if (c < -1 || c > 96)
			c = 3;
		if (c >= 0)
			ft_put_sprite_part_s(eng, eng->ascii_spr,
				(t_v2i){pos[0] + i * 7 * size + size, pos[1] + size},
				(t_rect_s){
				(t_v2i){c * 5, 0},
				(t_v2i){5, 7}, size});
		i++;
	}
}
