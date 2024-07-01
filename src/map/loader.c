/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 11:19:16 by alde-fre          #+#    #+#             */
/*   Updated: 2024/07/01 13:38:06 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static int	_ft_is_space(t_map *map, t_v2i pos)
{
	t_v2i	xy;
	int		flag;

	flag = 0;
	xy[1] = -1;
	while (xy[1] < 1)
	{
		xy[0] = -1;
		while (xy[0] < 1)
		{
			flag |= ((ft_get_map(map, pos + xy + (t_v2i){0, 0}) != '1')
					&& (ft_get_map(map, pos + xy + (t_v2i){1, 0}) != '1')
					&& (ft_get_map(map, pos + xy + (t_v2i){0, 1}) != '1')
					&& (ft_get_map(map, pos + xy + (t_v2i){1, 1}) != '1'));
			xy[0]++;
		}
		xy[1]++;
	}
	return (flag);
}

static t_entity	*_ft_add_ent(uint8_t cell, t_data *game, t_map *map, t_v2f pos)
{
	t_entity ent;
	if (cell == '0')
	{
		if ((rand() & 15) == 0)
		{
			ent = ft_ennemy_create(pos, 0.0f);
			return (ft_ent_add(game, &ent));
		}
		else if ((rand() % 25) * 2 <= ft_get_obj_prob(map,
				(t_v2i){(pos[0] - 16) / 32.0f, (pos[1] - 16) / 32.0f}))
		{
			ent = ft_object_create(rand() & 3, pos);
			return (ft_ent_add(game, &ent));
		}
	}
	else if (cell == 'P')
	{
		if (_ft_is_space(map, (t_v2i){(pos[0] - 16) / 32.0f,
				(pos[1] - 16) / 32.0f}))
			ent = ft_tank_create(game, pos);
		else
			ent = ft_rambo_create(game, pos);
		ft_ent_add(game, &ent);
		game->pindex = vector_size(&game->map->entities) - 1;
	}
	else if (cell == 'C')
	{
		ent = ft_coin_create(pos);
		return (ft_ent_add(game, &ent));
	}
	else if (cell == 'E')
	{
		ent = ft_exit_create(pos);
		return (ft_ent_add(game, &ent));
	}
	return ((t_entity *)1);
}

static int	_ft_temp(t_data *game, t_map *map)
{
	int		i;
	int		flag;

	i = -1;
	flag = 1;
	while (++i < map->size[0] * map->size[1])
		flag &= _ft_add_ent(
				ft_get_map(map, (t_v2i){i % map->size[0], i / map->size[0]}),
				game, map, (t_v2f){(i % map->size[0]) * 32 + 16,
				(i / map->size[0]) * 32 + 16}) != NULL;
	return (flag);
}

static int	ft_put_sprite_r3(t_data *game, t_v2i pos, t_rect i)
{
	t_v2i	dim;
	t_color	col;
	t_color	col2;

	dim[1] = 0;
	while (dim[1] < 32)
	{
		dim[0] = 0;
		while (dim[0] < 32)
		{
			col = ft_get_color(game->map->background, pos + dim);
			col2 = ft_get_color(game->spr[65], i.pos + dim);
			ft_draw(game->eng, pos + dim, ft_color_inter(col, col2, (col2.d >> 24) / 255.f));
			dim[0]++;
		}
		dim[1]++;
	}
	return (1);
}

static inline int	__get_tile_index(t_map *map, t_v2i const pos)
{
	int	index;

	index = 0;
	index = (index << 1) | (ft_get_map(map, pos + (t_v2i){0, -1}) == '1');
	index = (index << 1) | (ft_get_map(map, pos + (t_v2i){0, 1}) == '1');
	index = (index << 1) | (ft_get_map(map, pos + (t_v2i){-1, 0}) == '1');
	index = (index << 1) | (ft_get_map(map, pos + (t_v2i){1, 0}) == '1');
	return (index);
}

void	ft_map_load(t_data *game, t_map *map)
{
	int		flag;

	game->map = map;
	game->pindex = 999999999;
	flag = _ft_temp(game, map);
	game->state_time = 0.0f;
	if (game->pindex == 999999999 || flag == 0)
		return (ft_putstr_fd("Error: Failed to spawn the player/missing essenti"
				"al entities.\n", 2), game->state = 0, ft_map_unload(game));

	ft_eng_sel_spr(game->eng, map->wall_layer);
	ft_clear(game->eng, ft_color_d(0xFF000000));
	ft_eng_sel_spr(game->eng, map->background);
	t_v2i pix_tile_pos;
	pix_tile_pos[1] = 0;
	while (pix_tile_pos[1] < map->background->size[1])
	{
		pix_tile_pos[0] = 0;
		while (pix_tile_pos[0] < map->background->size[0])
		{
			t_v2i tile_pos = pix_tile_pos / 32;
			ft_put_sprite(game->eng, game->spr[2 + 31
				* (ft_get_map(game->map, tile_pos) == 'E')], pix_tile_pos);
			if (ft_get_map(game->map, tile_pos) == '0' || ft_get_map(game->map, tile_pos) == 'C')
			{
				if (ft_get_map(game->map, tile_pos + (t_v2i){0, -1}) == '1')
					ft_put_sprite_r3(game,
						pix_tile_pos,
						(t_rect){(t_v2i){32, 64}, {16, 16}});
				if (ft_get_map(game->map, tile_pos + (t_v2i){0, 1}) == '1')
					ft_put_sprite_r3(game,
						pix_tile_pos,
						(t_rect){{32, 0}, {16, 16}});
				if (ft_get_map(game->map, tile_pos + (t_v2i){1, 0}) == '1')
					ft_put_sprite_r3(game,
						pix_tile_pos,
						(t_rect){{0, 32}, {16, 16}});
				if (ft_get_map(game->map, tile_pos + (t_v2i){-1, 0}) == '1')
					ft_put_sprite_r3(game,
						pix_tile_pos,
						(t_rect){{64, 32}, {16, 16}});
			}
			else
			{
				ft_eng_sel_spr(game->eng, map->wall_layer);
				ft_put_sprite_part(game->eng, game->spr[3], pix_tile_pos,
					(t_rect){{__get_tile_index(game->map, tile_pos) * 32, 0}, {32, 32}});
				ft_eng_sel_spr(game->eng, map->background);
			}
			pix_tile_pos[0] += 32;
		}
		pix_tile_pos[1] += 32;
	}
	ft_eng_sel_spr(game->eng, NULL);


	game->eplay = vector_get(&map->entities, game->pindex);
	game->tplay = game->eplay->data;
	game->rplay = game->eplay->data;
	
	game->state = 1;
	game->map->bullet_time = 999.0f;
	game->score = 0.0f;
	game->crate_nb = 0;
	game->is_finished = 0;
	game->blood = 1000 + (rand() & 1023);
	game->shake = (t_v2f){0.0f, 0.0f};
	game->max_crate = vector_count_if(&map->entities, &ft_exit_count);
}

void	ft_map_unload(t_data *game)
{
	t_entity	*ent;

	while (vector_size(&game->map->entities))
	{
		ent = vector_pop(&game->map->entities);
		ent->destroy(ent, game);
	}
	vector_clear(&game->map->particles);
	game->map->active_nbr = 0;
	game->eplay = NULL;
	game->tplay = NULL;
	game->rplay = NULL;
	game->map = NULL;
}
