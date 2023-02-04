/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:11:23 by alde-fre          #+#    #+#             */
/*   Updated: 2023/02/04 14:36:05 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	ft_game_render(t_data *game)
{
	t_v2i	mouse;

	ft_game_render_map(game);
	ft_game_render_ent(game);
	ft_game_render_ui(game);
	mouse = ((t_v2i){game->eplay->pos[0], game->eplay->pos[1]}
			+ (((t_v2i){game->eng->mouse_x, game->eng->mouse_y}
					- (t_v2i){game->eng->win_x / 2, game->eng->win_y / 2})
				/ 6));
	game->cam.pos = mouse - game->cam.dim / 2;
	game->cam.pos += ft_v2irot((t_v2i){-game->shake * 20, 0},
			game->dplay->top_rot);
	return (1);
}

void	ft_game_render_ui(t_data *game)
{
	float		s;
	float		c;
	float		ratio;

	ratio = ft_min((game->dplay->fire_cool / 4.0f)
			* (game->dplay->fire_cool / 4.0f)
			* (game->dplay->fire_cool / 4.0f), 1.0f);
	s = sinf(game->dplay->fire_cool * 80) * 2 * ratio;
	c = cosf(game->dplay->fire_cool * 60.6) * 2 * ratio;
	ft_rect(game->eng, (t_v2i){36 + s, 6 + c}, (t_v2i){ft_min(
			game->dplay->fire_cool / 4.0f * 200, 200), 20},
		ft_color_inter(ft_color_d(0x900A00), ft_color_d(0x65A165),
			game->dplay->fire_cool / 4.0f));
	ft_put_sprite_s(game->eng, game->spr[19], (t_v2i){0, 0}, 2);
	ft_put_nbr(game->eng, (t_v2i){10, 40}, game->map->score / 32, 2);
}

int	ft_game_render_map(t_data *data)
{
	t_v2i	pos;
	t_v2i	rpos;
	t_v2i	wpos;

	pos[1] = -2;
	while (++pos[1] <= data->cam.dim[1] / 32 + 1)
	{
		pos[0] = -2;
		while (++pos[0] <= data->cam.dim[0] / 32 + 1)
		{
			rpos[0] = (pos[0]
					- (data->cam.pos[0] / 32. - data->cam.pos[0] / 32)) * 32;
			rpos[1] = (pos[1]
					- (data->cam.pos[1] / 32. - data->cam.pos[1] / 32)) * 32;
			wpos = pos + data->cam.pos / 32;
			if (ft_get_map(data->map, wpos) == 'E')
				ft_put_sprite(data->eng, data->spr[33], rpos);
			else
				ft_put_sprite(data->eng, data->spr[2], rpos);
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
	while (i < data->map->active_nbr - 1u)
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

int	ft_game_update_ent(t_data *data, float dt)
{
	t_entity	*ent;
	t_length	i;

	data->shake = fmax(0, data->shake - dt * 2);
	i = -1;
	while (++i < data->map->active_nbr)
	{
		ent = (t_entity *)ft_vector_get(data->map->entities, i);
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
	return (1);
}
