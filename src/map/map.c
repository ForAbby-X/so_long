/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 22:21:41 by alde-fre          #+#    #+#             */
/*   Updated: 2024/07/01 13:33:01 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static int	_ft_map_vectors_create(t_map *map)
{
	map->entities = vector_create(sizeof(t_entity));
	if (map->entities.data == NULL)
		return (0);
	map->particles = vector_create(sizeof(t_particle));
	if (map->particles.data == NULL)
		return (vector_destroy(&map->entities), 0);
	return (1);
}

t_map	ft_map_create(t_data *game, char *data, t_v2i size, char *name)
{
	t_map	map;

	map.data = data;
	map.active_nbr = 0;
	map.size = size;
	map.name = name;
	map.background = ft_sprite(game->eng, map.size[0] * 32,
			map.size[1] * 32);
	map.wall_layer = ft_sprite(game->eng, map.size[0] * 32,
			map.size[1] * 32);
	if (map.background == NULL)
		return (free(map.name), free(map.data), (t_map){0});
	if (_ft_map_vectors_create(&map) == 0)
		return (ft_destroy_sprite(game->eng, map.background),
			free(map.name), free(map.data), (t_map){0});
	return (map);
}

void	ft_maps_destroy(t_data *game)
{
	while (vector_size(&game->maps))
		ft_map_destroy(game, vector_pop(&game->maps));
	vector_destroy(&game->maps);
}

void	ft_map_destroy(t_data *game, t_map *map)
{
	t_entity	*ent;

	while (vector_size(&map->entities))
	{
		ent = vector_pop(&map->entities);
		ent->destroy(ent, game);
	}
	vector_destroy(&map->entities);
	vector_destroy(&map->particles);
	ft_destroy_sprite(game->eng, map->wall_layer);
	ft_destroy_sprite(game->eng, map->background);
	free(map->name);
	free(map->data);
}
