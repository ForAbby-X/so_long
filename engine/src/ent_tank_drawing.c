/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ent_tank_drawing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 07:53:59 by alde-fre          #+#    #+#             */
/*   Updated: 2022/11/28 16:47:55 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static int	ft_put_sprite_r2(t_data *game, t_sprite *spr,
			t_v2i pos, t_v2i cen, float rot)
{
	t_v2i	dim;
	t_v2i	read;
	t_v2i	bord[2];
	t_color	col;
	t_color	col2;

	_ft_get_border(spr, cen, rot, bord);
	dim.y = bord[0].y;
	while (dim.y <= bord[1].y)
	{
		dim.x = bord[0].x;
		while (dim.x <= bord[1].x)
		{
			read.x = floor(cen.x + cosf(rot) * dim.x + sinf(rot) * dim.y);
			read.y = floor(cen.y - sinf(rot) * dim.x + cosf(rot) * dim.y);
			col = ft_get_color(spr, read);
			col2 = ft_get_color(game->dplay->spr, ft_v2iadd(pos, dim));
			if ((col2.d >> 24) != 255 && (col.d >> 24) != 255)
				ft_draw(game->eng, ft_v2iadd(pos, dim),
					ft_color_inter(col, col2, 0.25f));
			dim.x++;
		}
		dim.y++;
	}
	return (1);
}

void	ft_paint_tank(t_data *game, t_entity *tank, t_entity *enn)
{
	t_v2f	spacing;
	t_v2i	pixel;

	spacing = ft_v2fsub(enn->pos, tank->pos);
	pixel = ft_v2iadd((t_v2i){33, 27},
			ft_v2irot((t_v2i){spacing.x, spacing.y}, -tank->rot));
	ft_eng_sel_spr(game->eng, ((t_dat_tank *)tank->data)->spr);
	ft_put_sprite_r2(game, game->spr[25], pixel, (t_v2i){32, 32}, tank->rot
		+ ft_rand(-1.0f, 1.0f));
	ft_eng_sel_spr(game->eng, 0);
}
