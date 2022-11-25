/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 19:44:54 by alde-fre          #+#    #+#             */
/*   Updated: 2022/11/25 07:01:05 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static int	ft_is_overlap(t_entity *ent_1, t_entity *ent_2)
{
	t_v2f	diff;
	float	max;

	diff = ft_v2fsub(ent_2->pos, ent_1->pos);
	max = ent_1->radius + ent_2->radius;
	if ((diff.x * diff.x + diff.y * diff.y) <= (max * max))
		return (1);
	return (0);
}

static void	ft_resolve_collision(t_entity *ent_1, t_entity *ent_2)
{
	t_v2f	diff;
	float	max;
	float	dist;
	t_v2f	dir;

	diff = ft_v2fsub(ent_2->pos, ent_1->pos);
	max = ent_1->radius + ent_2->radius;
	dist = ft_v2fmag(diff);
	dir = ft_v2fnorm(diff, (max - dist) * 0.5f);
	ent_1->pos = ft_v2fsub(ent_1->pos, dir);
	ent_2->pos = ft_v2fadd(ent_2->pos, dir);
}

void	ft_entity_collisions(t_data *game)
{
	t_length	i;
	t_length	j;
	t_entity	*ent_1;
	t_entity	*ent_2;

	i = 0;
	while (i < ft_vector_size(game->map.entities))
	{
		j = 0;
		while (j < ft_vector_size(game->map.entities))
		{
			if (i != j)
			{
				ent_1 = ft_vector_get(game->map.entities, i);
				ent_2 = ft_vector_get(game->map.entities, j);
				if (ent_1->type > 0 && ent_2->type > 0 
					&& ft_is_overlap(ent_1, ent_2))
					ft_resolve_collision(ent_1, ent_2);
			}
			j++;
		}
		i++;
	}
}
