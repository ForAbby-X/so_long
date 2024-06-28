/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 02:10:34 by alde-fre          #+#    #+#             */
/*   Updated: 2024/06/28 14:03:24 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

t_entity	ft_ent_create(int type, t_v2f pos, t_v2f dir, float radius)
{
	t_entity	ent;

	ent.data = (void *)NULL;
	ent.type = type;
	ent.pos = pos;
	ent.dir = dir;
	ent.radius = radius;
	ent.uuid = ft_get_uuid();
	ent.pressure = 0.0f;
	ent.alive = 1;
	return (ent);
}

t_entity	*ft_ent_add(t_data *game, t_entity *ent)
{
	if (ent == NULL)
		return (NULL);
	return (vector_addback(&game->map->entities, ent));
}

t_entity	*ft_ent_get(t_data *game, t_length index)
{
	return (vector_get(&game->map->entities, index));
}
