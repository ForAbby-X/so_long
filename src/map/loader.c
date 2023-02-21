/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 11:19:16 by alde-fre          #+#    #+#             */
/*   Updated: 2023/02/21 10:55:03 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static int	_ft_is_space(t_map *map, t_v2i pos)
{
	t_v2i	xy;
	int		flag;

	flag = 0;
	xy[1] = -2;
	while (++xy[1] < 1)
	{
		xy[0] = -2;
		while (++xy[0] < 1)
		{
			flag |= ((ft_get_map(map, pos + xy + (t_v2i){0, 0}) != '1')
					&& (ft_get_map(map, pos + xy + (t_v2i){0, 0}) != '1')
					&& (ft_get_map(map, pos + xy + (t_v2i){0, 0}) != '1')
					&& (ft_get_map(map, pos + xy + (t_v2i){0, 0}) != '1'));
		}
	}
	return (flag);
}

static t_entity	*_ft_add_ent(uint8_t cell, t_data *game, t_map *map, t_v2f pos)
{
	if (cell == '0')
	{
		if ((rand() & 15) == 0)
			return (ft_ent_add(game, ft_ennemy_create(pos, 0.0f)));
		else if ((rand() % 25) * 2 <= ft_get_obj_prob(map,
				(t_v2i){(pos[0] - 16) / 32.0f, (pos[1] - 16) / 32.0f}))
			return (ft_ent_add(game, ft_object_create(rand() & 3, pos)));
	}
	if (cell == 'P')
	{
		if (_ft_is_space(map, (t_v2i){(pos[0] - 16) / 32.0f,
				(pos[1] - 16) / 32.0f}))
			game->eplay = ft_ent_add(game, ft_tank_create(game, pos));
		else
			game->eplay = ft_ent_add(game, ft_rambo_create(game, pos));
	}
	if (cell == 'C')
		return (ft_ent_add(game, ft_coin_create(pos)));
	if (cell == 'E')
		return (ft_ent_add(game, ft_exit_create(pos)));
	return ((t_entity *)1);
}

static int	_ft_temp(t_data *game, t_map *map)
{
	int		i;
	int		flag;

	i = -1;
	flag = 1;
	while (++i < map->size[0] * map->size[1])
	{
		flag &= _ft_add_ent(
				ft_get_map(map, (t_v2i){i % map->size[0], i / map->size[0]}),
				game, map, (t_v2f){(i % map->size[0]) * 32 + 16,
				(i / map->size[0]) * 32 + 16}) != NULL;
	}
	return (flag);
}

void	ft_map_load(t_data *game, t_map *map)
{
	int		flag;

	game->map = map;
	ft_eng_sel_spr(game->eng, map->background);
	ft_clear(game->eng, ft_color_d(0xFF000000));
	ft_eng_sel_spr(game->eng, NULL);
	flag = _ft_temp(game, map);
	game->state_time = 0.0f;
	if (game->eplay == NULL || flag == 0)
	{
		ft_putstr_fd("Error: Failed to spawn the player/missing essential entit"
			"ies.\n", 2);
		game->state = 0;
		ft_map_unload(game);
		return ;
	}
	if (game->eplay->type == 0)
		game->tplay = game->eplay->data;
	if (game->eplay->type == 1)
		game->rplay = game->eplay->data;
	game->state = 1;
	game->map->bullet_time = 999.0f;
	game->score = 0.0f;
	game->crate_nb = 0;
	game->is_finished = 0;
	game->max_crate = ft_vector_countif(map->entities, &ft_exit_count);
}

void	ft_map_unload(t_data *game)
{
	t_entity	*ent;

	while (ft_vector_size(game->map->entities))
	{
		ent = ft_vector_pop(game->map->entities);
		ent->destroy(ent, game);
	}
	while (ft_vector_size(game->map->particles))
		free(ft_vector_pop(game->map->particles));
	game->map->active_nbr = 0;
	game->eplay = NULL;
	game->tplay = NULL;
	game->rplay = NULL;
	game->map = NULL;
}
