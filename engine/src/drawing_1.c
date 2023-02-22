/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 10:15:32 by alde-fre          #+#    #+#             */
/*   Updated: 2023/01/27 13:55:22 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	ft_draw(t_engine *eng, t_v2i pos, t_color color)
{
	size_t	index;

	if ((color.d >> 24) == 255 || pos[0] < 0 || pos[1] < 0
		|| (size_t)pos[0] >= ft_eng_size_x(eng)
		|| (size_t)pos[1] >= ft_eng_size_y(eng))
		return ;
	index = pos[0] + pos[1] * ft_eng_size_x(eng);
	eng->sel_spr->data[index] = color;
}

void	ft_clear(t_engine *eng, t_color color)
{
	size_t	index;

	index = 0;
	while (index < ft_eng_size_x(eng) * ft_eng_size_y(eng))
	{
		eng->sel_spr->data[index] = color;
		index++;
	}
}

static void	ft_pt_circle(t_engine *eng, t_v2i pos, t_v2i dim, t_color color)
{
	ft_draw(eng, pos + dim, color);
	ft_draw(eng, (t_v2i){pos[0] - dim[0], pos[1] + dim[1]}, color);
	ft_draw(eng, (t_v2i){pos[0] + dim[0], pos[1] - dim[1]}, color);
	ft_draw(eng, pos - dim, color);
	ft_draw(eng, (t_v2i){pos[0] + dim[1], pos[1] + dim[0]}, color);
	ft_draw(eng, (t_v2i){pos[0] - dim[1], pos[1] + dim[0]}, color);
	ft_draw(eng, (t_v2i){pos[0] + dim[1], pos[1] - dim[0]}, color);
	ft_draw(eng, (t_v2i){pos[0] - dim[1], pos[1] - dim[0]}, color);
}

void	ft_circle(t_engine *eng, t_v2i pos, int r, t_color color)
{
	t_v2i	dim;
	int		d;

	dim[0] = 0;
	dim[1] = r;
	d = 3 - 2 * r;
	ft_pt_circle(eng, pos, dim, color);
	while (dim[1] >= dim[0])
	{
		dim[0]++;
		if (d > 0)
		{
			dim[1]--;
			d = d + 4 * (dim[0] - dim[1]) + 10;
		}
		else
			d = d + 4 * dim[0] + 6;
		ft_pt_circle(eng, pos, dim, color);
	}
}

void	ft_rect(t_engine *eng, t_v2i pos, t_v2i dim, t_color color)
{
	t_v2i	p;

	p[1] = 0;
	while (p[1] < dim[1])
	{
		p[0] = 0;
		while (p[0] < dim[0])
		{
			ft_draw(eng, pos + p, color);
			p[0]++;
		}
		p[1]++;
	}
}
