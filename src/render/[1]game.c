/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [1]game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:11:23 by alde-fre          #+#    #+#             */
/*   Updated: 2023/03/04 12:10:26 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	ft_game_render_ui_end(t_data *game)
{
	ft_shader(game, game->spr[63], 1.f);
	if (game->eplay->pos[0] > 0.0f)
		ft_put_text(game->eng, (t_v2i){221, 169}, "vivant", 2);
	else
		ft_put_text(game->eng, (t_v2i){221, 169}, "mort", 2);
	if (game->crate_nb == game->max_crate)
		ft_put_text(game->eng, (t_v2i){154, 213}, "atteint", 2);
	else
		ft_put_text(game->eng, (t_v2i){154, 213}, "manque", 2);
	ft_put_nbr(game->eng, (t_v2i){221, 256}, game->crate_nb, 2);
	ft_put_nbr(game->eng, (t_v2i){248, 278}, game->score, 2);
	ft_put_nbr(game->eng, (t_v2i){183, 323}, game->blood, 2);
}

int	ft_game_render(t_data *game, float dt)
{
	t_v2i	mouse;

	ft_game_render_map(game);
	ft_game_render_ent(game);
	ft_game_all_par(game, dt);
	if (game->is_finished)
		return (ft_game_render_ui_end(game), 1);
	if (game->eplay->type == 0)
		ft_shader(game, game->spr[60], (1.0f - game->tplay->health / 2000.0f));
	if (game->eplay->type == 1)
		ft_shader(game, game->spr[58], (1.0f - game->rplay->health / 1000.0f));
	ft_game_render_ui_1(game);
	mouse = ((t_v2i){game->eplay->pos[0], game->eplay->pos[1]}
			+ (((t_v2i){game->eng->mouse_x, game->eng->mouse_y}
					- (t_v2i){game->eng->win_x / 2, game->eng->win_y / 2})
				/ 6));
	game->cam.pos = mouse - game->cam.dim / 2;
	game->cam.pos += (t_v2i){game->shake[0], game->shake[1]};
	return (1);
}

int	ft_game_render_map(t_data *data)
{
	t_v2i	pos;
	t_v2i	rpos;
	t_v2i	wpos;

	pos[1] = -2;
	while (++pos[1] <= data->cam.dim[1] / 32 + 1)
	{
		rpos[1] = (pos[1]
				- (data->cam.pos[1] / 32.f - data->cam.pos[1] / 32)) * 32;
		pos[0] = -2;
		while (++pos[0] <= data->cam.dim[0] / 32 + 1)
		{
			rpos[0] = (pos[0]
					- (data->cam.pos[0] / 32.f - data->cam.pos[0] / 32)) * 32;
			wpos = pos + data->cam.pos / 32;
			ft_put_sprite(data->eng, data->spr[2 + 31
				* (ft_get_map(data->map, wpos) == 'E')], rpos);
			if (ft_get_map(data->map, wpos) == '1')
				ft_put_sprite(data->eng, data->spr[3], rpos);
			else
				ft_put_sprite_part(data->eng, data->map->background, rpos,
					(t_rect){wpos * 32, (t_v2i){32, 32}});
		}
	}
	return (1);
}

void	ft_game_render_ent(t_data *data)
{
	t_entity	*ent[3];
	t_length	i;

	i = 0;
	while (data->map->active_nbr && i < data->map->active_nbr - 1u)
	{
		ent[0] = ft_vector_get(data->map->entities, i);
		ent[1] = ft_vector_get(data->map->entities, i + 1);
		if (ent[0]->type < ent[1]->type)
		{
			ent[2] = data->map->entities->data[i];
			data->map->entities->data[i] = data->map->entities->data[i + 1];
			data->map->entities->data[i + 1] = ent[2];
			i = 0;
		}
		else
			i++;
	}
	i = 0;
	while (i < data->map->active_nbr)
	{
		ent[0] = (t_entity *)ft_vector_get(data->map->entities, i++);
		ent[0]->display(ent[0], data);
	}
}

void	ft_game_update_ent(t_data *data, float dt)
{
	t_entity	*ent;
	t_length	i;

	data->shake -= data->shake * 1000.0f * dt * dt;
	i = 0;
	while (i < data->map->active_nbr)
	{
		ent = (t_entity *)ft_vector_get(data->map->entities, i++);
		ent->update(ent, data, dt);
		ent->pressure = 0.0f;
	}
	i = 0;
	while (i < ft_vector_size(data->map->entities))
	{
		ent = (t_entity *)ft_vector_get(data->map->entities, i);
		if (ent->alive == 0)
		{
			ent->destroy(ent, data);
			ft_vector_rem(data->map->entities, i);
			if (i < data->map->active_nbr)
				data->map->active_nbr--;
		}
		else
			i++;
	}
}
