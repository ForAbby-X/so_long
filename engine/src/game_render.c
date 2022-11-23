/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:11:23 by alde-fre          #+#    #+#             */
/*   Updated: 2022/11/23 17:08:56 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	ft_game_render(t_data *game)
{
	t_v2i	mouse;

	ft_game_render_map(game);
	ft_game_render_ent(game);
	ft_game_render_ui(game);
	mouse = ft_v2iadd(ft_v2i(game->player->pos.x, game->player->pos.y),
			ft_v2idiv(ft_v2isub(ft_v2i(game->eng->mouse_x, game->eng->mouse_y),
					ft_v2i(game->eng->win_x / 2, game->eng->win_y / 2)), 6));
	game->cam.pos = ft_v2isub(mouse, ft_v2idiv(game->cam.dim, 2));
	game->cam.pos = ft_v2iadd(game->cam.pos, ft_v2irot(
				ft_v2i(-game->shake * 20, 0), game->player->top_rot));
	return (1);
}

void	ft_game_render_ui(t_data *game)
{
	float		s;
	float		c;
	float		ratio;

	ratio = ft_min((game->player->fire_cool / 4.0f)
			* (game->player->fire_cool / 4.0f)
			* (game->player->fire_cool / 4.0f), 1.0f);
	s = sinf(game->player->fire_cool * 80) * 2 * ratio;
	c = cosf(game->player->fire_cool * 60.6) * 2 * ratio;
	ft_rect(game->eng, ft_v2i(36 + s, 6 + c), ft_v2i(ft_min(
				game->player->fire_cool / 4.0f * 200, 200), 20),
		ft_color_inter(ft_color_d(0x900A00), ft_color_d(0x65A165),
			game->player->fire_cool / 4.0f));
	ft_put_sprite_s(game->eng, game->spr[19], ft_v2i(0, 0), 2);
}

int	ft_game_render_map(t_data *data)
{
	t_v2i	pos;
	t_v2i	rpos;
	t_v2i	wpos;

	pos.y = -1;
	while (pos.y <= data->cam.dim.y / 32 + 1)
	{
		pos.x = -1;
		while (pos.x <= data->cam.dim.x / 32 + 1)
		{
			rpos.x
				= (pos.x - (data->cam.pos.x / 32. - data->cam.pos.x / 32)) * 32;
			rpos.y
				= (pos.y - (data->cam.pos.y / 32. - data->cam.pos.y / 32)) * 32;
			wpos = ft_v2iadd(pos, ft_v2idiv(data->cam.pos, 32));
			ft_put_sprite_solid(data->eng, data->spr[2], rpos);
			ft_put_sprite_part(data->eng, data->map.background, rpos,
				(t_rect){ft_v2imul(wpos, 32), (t_v2i){32, 32}});
			if (ft_get_map(&data->map, wpos))
				ft_put_sprite_solid(data->eng, data->spr[3], rpos);
			pos.x++;
		}
		pos.y++;
	}
	return (1);
}

int	ft_game_render_ent(t_data *data)
{
	t_entity	*ent[3];
	t_length	i;

	i = 0;
	while (i < ft_vector_size(data->map.entities) - 1)
	{
		ent[0] = (t_entity *)ft_vector_get(data->map.entities, i);
		ent[1] = (t_entity *)ft_vector_get(data->map.entities, i + 1);
		if (ent[0]->type < ent[1]->type)
		{
			ent[2] = data->map.entities->data[i];
			data->map.entities->data[i] = data->map.entities->data[i + 1];
			data->map.entities->data[i + 1] = ent[2];
			i = 0;
		}
		else
			i++;
	}
	i = 0;
	while (i < ft_vector_size(data->map.entities))
	{
		ent[0] = (t_entity *)ft_vector_get(data->map.entities, i++);
		ent[0]->display(ent[0], data);
	}
	return (1);
}

int	ft_game_upd_ent(t_data *data, float dt)
{
	t_entity	*ent;
	t_length	i;

	data->shake = fmax(0, data->shake - dt * 2);
	i = 0;
	while (i < ft_vector_size(data->map.entities))
	{
		ent = (t_entity *)ft_vector_get(data->map.entities, i);
		ent->update(ent, data, dt);
		i++;
	}
	i = 0;
	while (i < ft_vector_size(data->map.entities))
	{
		ent = (t_entity *)ft_vector_get(data->map.entities, i);
		if (ent->alive == 0)
		{
			ent->destroy(ent, data);
			ft_vector_rem(data->map.entities, i);
		}
		else
			i++;
	}
	return (1);
}
