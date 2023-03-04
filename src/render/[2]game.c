/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [2]game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:11:26 by alde-fre          #+#    #+#             */
/*   Updated: 2023/03/04 12:09:53 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	ft_game_all_par(t_data *data, float dt)
{
	t_length	i;
	t_particle	*par;

	i = 0;
	while (i < ft_vector_size(data->map->particles))
	{
		par = (t_particle *)ft_vector_get(data->map->particles, i);
		par->pos = par->pos + par->dir * dt;
		par->time += dt;
		ft_put_sprite(data->eng, par->spr,
			(t_v2i){par->pos[0] - data->cam.pos[0],
			par->pos[1] - data->cam.pos[1]} - par->off);
		if (par->time >= par->life_time)
		{
			free(par);
			ft_vector_rem(data->map->particles, i);
		}
		else
			i++;
	}
	return (1);
}

void	ft_shader(t_data *gam, t_sprite *spr, float ratio)
{
	size_t	index;
	t_color	col[2];
	uint8_t	alpha;

	ratio = fminf(fmax(ratio, 0.0f), 1.0f);
	index = 0;
	while (index < gam->eng->win_x * gam->eng->win_y)
	{
		col[0] = gam->eng->sel_spr->data[index];
		col[1] = spr->data[index];
		alpha = col[1].a;
		gam->eng->sel_spr->data[index]
			= ft_color_inter(col[1], col[0], ratio * (alpha / 255.0f));
		index++;
	}
}

void	ft_game_render_ui_1(t_data *game)
{
	int	min;

	if (game->is_finished)
	{
		ft_put_text(game->eng, (t_v2i){game->eng->win_x / 2 - 6 * 4 * 7,
			game->eng->win_y / 2 - 36}, "YOU ARE DEAD", 4);
		return ;
	}
	if (game->eplay->type == 0)
	{
		min = ft_min(game->tplay->fire_cool[1] * 18.75f, 75);
		ft_put_sprite_part_s(game->eng, game->spr[51], (t_v2i){2, 2},
			(t_rect_s){{0, 0}, {43 + min, 36}, 2});
		ft_put_sprite_part_s(game->eng, game->spr[50], (t_v2i){88 + min * 2, 2},
			(t_rect_s){{43 + min, 0}, {75 - min, 36}, 2});
		if (game->tplay->fire_cool[1] > 4.0f && ((int)(game->time * 2) & 1))
			ft_put_text(game->eng, (t_v2i){10, 10}, "[RC] to shoot !", 2);
		ft_put_text(game->eng, (t_v2i){game->eng->win_x / 2 - 10 * 14,
			game->eng->win_y - 20}, "[SPACE] self destruct", 2);
	}
	ft_game_render_ui_2(game);
}

void	ft_game_render_ui_2(t_data *game)
{
	int	min;

	if (game->eplay->type == 1)
	{
		min = ft_min(game->rplay->health / 1000.f * 37.f, 37);
		ft_put_sprite_part_s(game->eng, game->spr[61], (t_v2i){2, 2},
			(t_rect_s){{0, 0}, {23, 37 - min}, 2});
		ft_put_sprite_part_s(game->eng, game->spr[62],
			(t_v2i){2, 2 + (37 - min) * 2},
			(t_rect_s){{0, 37 - min}, {23, min}, 2});
		ft_put_nbr(game->eng, (t_v2i){10, 10}, (int)game->rplay->health, 2);
	}
	ft_put_sprite(game->eng, game->spr[19], (t_v2i){10, 72 + 5});
	ft_put_sprite(game->eng, game->spr[28], (t_v2i){10, 72 + 41});
	ft_put_nbr(game->eng, (t_v2i){26, 72 + 24}, game->score / 32, 2);
	ft_put_nbr(game->eng, (t_v2i){26, 72 + 59}, game->crate_nb, 2);
	ft_put_text(game->eng, (t_v2i){36, 82 + 59}, "/", 2);
	ft_put_nbr(game->eng, (t_v2i){36 + 7 * 2, 82 + 59}, game->max_crate, 2);
}
