/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 22:21:41 by alde-fre          #+#    #+#             */
/*   Updated: 2023/02/03 15:53:56 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static int	_ft_map_vectors_create(t_map *map)
{
	map->entities = ft_vector_create(1024);
	if (map->entities == NULL)
		return (0);
	map->particles = ft_vector_create(1024);
	if (map->particles == NULL)
		return (ft_vector_destroy(map->entities), 0);
	return (1);
}

t_map	*ft_map_create(t_data *game, char *data, t_v2i size, char *name)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (map == NULL)
		return (free(name), free(data), NULL);
	map->data = data;
	map->active_nbr = 0;
	map->size = size;
	map->name = name;
	map->background = ft_sprite(game->eng, map->size[0] * 32,
			map->size[1] * 32);
	if (map->background == NULL)
		return (free(map->name), free(map->data), free(map), NULL);
	if (_ft_map_vectors_create(map) == 0)
		return (ft_destroy_sprite(game->eng, map->background),
			free(map->name), free(map->data), free(map), NULL);
	return (map);
}

void	ft_maps_destroy(t_data *game)
{
	while (ft_vector_size(game->maps))
		ft_map_destroy(game, ft_vector_pop(game->maps));
	ft_vector_destroy(game->maps);
}

void	ft_map_destroy(t_data *game, t_map *map)
{
	t_entity	*ent;

	while (ft_vector_size(map->entities))
	{
		ent = ft_vector_pop(map->entities);
		ent->destroy(ent, game);
	}
	while (ft_vector_size(map->particles))
		free(ft_vector_pop(map->particles));
	ft_vector_destroy(map->entities);
	ft_vector_destroy(map->particles);
	ft_destroy_sprite(game->eng, map->background);
	free(map->name);
	free(map->data);
	free(map);
}
