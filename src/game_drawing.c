/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_drawing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 09:35:55 by alde-fre          #+#    #+#             */
/*   Updated: 2022/12/23 18:46:53 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h" 

int	ft_drawh(t_data *game, t_v2i pos, t_color color, uint8_t height)
{
	size_t	index;

	(void)height;
	if (color.a == 255 || pos[0] < 0 || pos[1] < 0
		|| (size_t)pos[0] >= ft_eng_size_x(game->eng)
		|| (size_t)pos[1] >= ft_eng_size_x(game->eng))
		return (0);
	index = pos[1] * game->eng->sel_spr->size[0] + pos[0];
	game->eng->sel_spr->data[index] = color;
	return (1);
}

int	ft_put_sprite_h(t_data *game, t_sprite *spr, t_v2i pos)
{
	t_v2i	dim;

	dim[1] = 0;
	while (dim[1] < spr->size[1])
	{
		dim[0] = 0;
		while (dim[0] < spr->size[0])
		{
			ft_drawh(game, ft_v2iadd(pos, dim), ft_get_color(spr, dim),
				ft_get_color(spr + 1, dim).r);
			dim[0]++;
		}
		dim[1]++;
	}
	return (1);
}

int	ft_put_sprite_rh(t_data *game, t_sprite *spr,
			t_v2i pos, t_v2i cen, float rot)
{
	t_v2i	dim;
	t_v2i	read;
	t_v2i	bord[2];

	ft_get_border(spr, cen, rot, bord);
	dim[1] = bord[0][1];
	while (dim[1] <= bord[1][1])
	{
		dim[0] = bord[0][0];
		while (dim[0] <= bord[1][0])
		{
			read[0] = floor(cen[0] + cosf(rot) * dim[0] + sinf(rot) * dim[1]);
			read[1] = floor(cen[1] - sinf(rot) * dim[0] + cosf(rot) * dim[1]);
			ft_drawh(game, ft_v2iadd(pos, dim), ft_get_color(spr, read),
				ft_get_color(spr + 1, read).r);
			dim[0]++;
		}
		dim[1]++;
	}
	return (1);
}
