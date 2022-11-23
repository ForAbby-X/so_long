/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_drawing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 09:35:55 by alde-fre          #+#    #+#             */
/*   Updated: 2022/11/23 15:39:27 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h" 

int	ft_drawh(t_data *game, t_v2i pos, t_color color, uint8_t height)
{
	size_t	index;

	(void)height;
	if (color.a == 255 || pos.x < 0 || pos.y < 0
		|| (size_t)pos.x >= ft_eng_size_x(game->eng)
		|| (size_t)pos.y >= ft_eng_size_x(game->eng))
		return (0);
	index = pos.y * game->eng->sel_spr->size.x + pos.x;
	game->eng->sel_spr->data[index] = color;
	return (1);
}

int	ft_put_sprite_h(t_data *game, t_sprite *spr, t_v2i pos)
{
	t_v2i	dim;

	dim.y = 0;
	while (dim.y < spr->size.y)
	{
		dim.x = 0;
		while (dim.x < spr->size.x)
		{
			ft_drawh(game, ft_v2iadd(pos, dim), ft_get_color(spr, dim),
				ft_get_color(spr + 1, dim).r);
			dim.x++;
		}
		dim.y++;
	}
	return (1);
}

static void	ft_get_border(t_sprite *spr,
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

int	ft_put_sprite_rh(t_data *game, t_sprite *spr,
			t_v2i pos, t_v2i cen, float rot)
{
	t_v2i	dim;
	t_v2i	read;
	t_v2i	bord[2];

	ft_get_border(spr, cen, rot, bord);
	dim.y = bord[0].y;
	while (dim.y <= bord[1].y)
	{
		dim.x = bord[0].x;
		while (dim.x <= bord[1].x)
		{
			read.x = floor(cen.x + cosf(rot) * dim.x + sinf(rot) * dim.y);
			read.y = floor(cen.y - sinf(rot) * dim.x + cosf(rot) * dim.y);
			ft_drawh(game, ft_v2iadd(pos, dim), ft_get_color(spr, read),
				ft_get_color(spr + 1, read).r);
			dim.x++;
		}
		dim.y++;
	}
	return (1);
}
