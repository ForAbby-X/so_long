/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 11:19:16 by alde-fre          #+#    #+#             */
/*   Updated: 2023/01/30 14:12:29 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	ft_map_load(t_data *game, t_map *map)
{
	int		i;
	uint8_t	cell;

	game->map = map;
	ft_eng_sel_spr(game->eng, map->background);
	ft_clear(game->eng, ft_color_d(0xFF000000));
	ft_eng_sel_spr(game->eng, NULL);
	i = -1;
	while (++i < map->size[0] * map->size[1])
	{
		cell = ft_get_map(map, (t_v2i){i % map->size[0], i / map->size[0]});
		if (cell == '0')
		{
			if ((rand() & 15) == 0)
			{
				ft_ent_add(game, ft_ennemy_create(
						(t_v2f){(i % map->size[0]) * 32 + 16,
						(i / map->size[0]) * 32 + 16}, 0.0f));
			}
			else if ((rand() % 25) <= ft_get_obj_prob(map,
					(t_v2i){i % map->size[0], i / map->size[0]}) / 1.3)
			{
				ft_ent_add(game, ft_object_create(rand() & 3,
						(t_v2f){(i % map->size[0]) * 32 + 16,
						(i / map->size[0]) * 32 + 16}));
			}
		}
		if (cell == 'P')
			game->eplay = ft_ent_add(game, ft_tank_create(game,
						(t_v2f){(i % map->size[0]) * 32 + 16,
						(i / map->size[0]) * 32 + 16}));
		if (cell == 'C')
			ft_ent_add(game, ft_coin_create((t_v2f){(i % map->size[0]) * 32
					+ 16, (i / map->size[0]) * 32 + 16}));
		if (cell == 'E')
			ft_ent_add(game, ft_exit_create((t_v2f){(i % map->size[0]) * 32
					+ 16, (i / map->size[0]) * 32 + 16}));
	}
	if (game->eplay == NULL)
		return (ft_putstr_fd("Error: Failed to spawn the player.\n", 2),
			ft_map_unload(game));
	game->dplay = game->eplay->data;
	game->state = 1;
	game->state_time = 0.0f;
	game->map->score = 0.0f;
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
	game->dplay = NULL;
	game->map = NULL;
}
