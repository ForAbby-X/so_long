/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ent_tank_drawing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 07:53:59 by alde-fre          #+#    #+#             */
/*   Updated: 2022/12/23 19:31:38 by alde-fre         ###   ########.fr       */
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

	ft_get_border(spr, cen, rot, bord);
	dim[1] = bord[0][1];
	while (dim[1] <= bord[1][1])
	{
		dim[0] = bord[0][0];
		while (dim[0] <= bord[1][0])
		{
			read[0] = floor(cen[0] + cosf(rot) * dim[0] + sinf(rot) * dim[1]);
			read[1] = floor(cen[1] - sinf(rot) * dim[0] + cosf(rot) * dim[1]);
			col = ft_get_color(spr, read);
			col2 = ft_get_color(game->dplay->spr, pos + dim);
			if ((col2.d >> 24) != 255 && (col.d >> 24) != 255)
				ft_draw(game->eng, pos + dim,
					ft_color_inter(col, col2, 0.25f));
			dim[0]++;
		}
		dim[1]++;
	}
	return (1);
}

void	ft_paint_tank(t_data *game, t_entity *tank, t_entity *enn)
{
	t_v2f	spacing;
	t_v2i	pixel;

	spacing = enn->pos - tank->pos;
	pixel = (t_v2i){33, 27} + ft_v2irot((t_v2i){spacing[0], spacing[1]},
			-tank->rot);
	ft_eng_sel_spr(game->eng, ((t_dat_tank *)tank->data)->spr);
	ft_put_sprite_r2(game, game->spr[25], pixel, (t_v2i){32, 32}, tank->rot
		+ ft_rand(-1.0f, 1.0f));
	ft_eng_sel_spr(game->eng, 0);
}
