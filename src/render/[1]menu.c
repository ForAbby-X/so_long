/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [1]menu.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:11:46 by alde-fre          #+#    #+#             */
/*   Updated: 2024/06/28 11:21:35 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static int	_ft_display_menu(t_data *game, t_map *map, int i)
{
	ft_rect(game->eng, (t_v2i){33, 50 + 180 + i * 12 * 3}, (t_v2i){7 * 3
		* ft_strlen(map->name), 9 * 3}, ft_color_d(0x191970));
	if (game->eng->mouse_x >= 33 && game->eng->mouse_x < 33 + 21
		* (int)ft_strlen(map->name) && game->eng->mouse_y >= 50 + 180 + i * 12
		* 3 && game->eng->mouse_y < 257 + i * 12 * 3)
	{
		ft_rect(game->eng, (t_v2i){30, 50 + 177 + i * 12 * 3}, (t_v2i){7 * 3
			* ft_strlen(map->name), 9 * 3}, ft_color_d(0x6495ED));
		ft_put_text(game->eng, (t_v2i){30, 227 + i * 12 * 3}, map->name, 3);
		return (1);
	}
	ft_put_text(game->eng, (t_v2i){33, 50 + 180 + i * 12 * 3}, map->name, 3);
	return (0);
}

static	void	_ft_3dbackground(t_data *game)
{
	t_v2i	p;
	t_v2f	pj;
	t_v2i	pix_pos;
	t_color	pix;

	p[1] = 0;
	while (p[1] < (int)game->eng->win_y)
	{
		p[0] = 0;
		while (p[0] < (int)game->eng->win_x)
		{
			pj[0] = ((float)p[0] / game->eng->win_x * 2) - 1.0f;
			pj[1] = ((float)p[1] / game->eng->win_y * 2) - 1.0f;
			pix_pos[0] = pj[0] / pj[1] * 100.0 + game->time * 20 + 2000;
			pix_pos[1] = 1.0 / pj[1] * 100.0;
			pix = game->spr[2 + (((pix_pos[0] / 32 + pix_pos[1] / 32 / 2) & 3) \
			== 0 && ((pix_pos[1] / 32) & 3) == 0)]->data[(pix_pos[0] & 31) \
			+ (31 - (pix_pos[1] & 31)) * 32];
			ft_draw(game->eng, (t_v2i){p[0], p[1]},
				ft_color_inter(pix, (t_color){0x067790}, fmax(0, pj[1] * 6)));
			p[0]++;
		}
		p[1]++;
	}
}

void	ft_menu(t_data *game, t_vector	*maps)
{
	int		i;
	int		sel;

	ft_clear(game->eng, ft_color_d(0x336600));
	_ft_3dbackground(game);
	ft_put_sprite_s(game->eng, game->spr[29 + ((int)(game->time * 4) & 1)],
		(t_v2i){ft_eng_size_x(game->eng) * 0.55,
		ft_eng_size_y(game->eng) * 0.55}, 6);
	ft_put_sprite(game->eng, game->spr[27], (t_v2i){29, 36});
	ft_put_text(game->eng, (t_v2i){30, 180}, "Choisis une carte:", 4);
	i = -1;
	sel = -1;
	while (++i < ((int)vector_size(maps)))
		if (_ft_display_menu(game, vector_get(maps, i), i))
			sel = i;
	ft_put_text(game->eng, (t_v2i){3, ft_eng_size_y(game->eng) - 9 * 2},
		"[Esc] Quitter", 2);
	if (sel >= 0 && game->eng->mouse[1])
		ft_map_load(game, vector_get(maps, sel));
}

void	ft_entry(t_data *game)
{
	t_v2i	pos;
	t_color	col;

	pos[1] = -1;
	while (++pos[1] < (int)ft_eng_size_y(game->eng))
	{
		pos[0] = -1;
		while (++pos[0] < (int)ft_eng_size_x(game->eng))
		{
			col = ft_get_color(game->eng->screen, (t_v2i){pos[0], pos[1]});
			col = ft_color_inter((t_color){0}, col, game->state_time / 4.0f);
			ft_draw(game->eng, pos, col);
		}
	}
	ft_put_text(game->eng, (t_v2i){ft_eng_size_x(game->eng) / 2
		- ft_strlen(game->map->name) * 14, ft_eng_size_y(game->eng) / 2
		- 4 * 4}, game->map->name, 4);
	if (game->state_time > 2.0f)
	{
		game->state = 2;
		game->state_time = 0.0f;
	}
}
