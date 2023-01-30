/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 19:44:54 by alde-fre          #+#    #+#             */
/*   Updated: 2023/01/30 14:51:49 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static int	ft_is_overlap_circle(t_entity *ent_1, t_entity *ent_2)
{
	t_v2f	diff;
	float	max;

	diff = ent_2->pos - ent_1->pos;
	max = ent_1->radius + ent_2->radius;
	if ((diff[0] * diff[0] + diff[1] * diff[1]) <= (max * max))
		return (1);
	return (0);
}

static void	ft_resolve_collision_circle(t_entity *ent_1, t_entity *ent_2)
{
	t_v2f	diff;
	float	max;
	float	dist;
	t_v2f	dir;
	float	mass;

	diff = ent_2->pos - ent_1->pos;
	max = ent_1->radius * ent_1->radius + ent_2->radius * ent_2->radius;
	dist = ft_v2fmag(diff);
	dir = ft_v2fnorm(diff, (ent_1->radius + ent_2->radius - dist));
	mass = ent_1->radius * ent_1->radius / max;
	ent_1->pos = ent_1->pos - dir * (1.0f - mass);
	ent_2->pos = ent_2->pos + dir * mass;
	ent_1->pressure += ft_v2fmag(dir * (1.0f - mass));
	ent_2->pressure += ft_v2fmag(dir * mass);
}

static void	ft_resolve_collision_square(t_data *game, t_entity *ent, float dt)
{
	t_v2i	cell;
	t_v2f	c[3];
	float	over;

	c[1] = (ent->pos + ent->dir * dt) / 32;
	cell[1] = (int)fmaxf(ent->pos[1] / 32 - 1, 0) - 1;
	while (++cell[1] <= fminf(ent->pos[1] / 32 + 1, game->map->size[1]))
	{
		cell[0] = (int)fmaxf(ent->pos[0] / 32 - 1, 0) - 1;
		while (++cell[0] <= fminf(ent->pos[0] / 32 + 1, game->map->size[0]))
		{
			if (ft_get_map(game->map, cell) == '1')
			{
				c[0][0] = fmaxf(cell[0], fminf(c[1][0], cell[0] + 1));
				c[0][1] = fmaxf(cell[1], fminf(c[1][1], cell[1] + 1));
				c[2] = c[0] - c[1];
				over = ent->radius / 32.0f - ft_v2fmag(c[2]);
				if (isnan(over))
					over = 0;
				if (over > 0)
				{
					ent->pos = ent->pos - ft_v2fnorm(c[2], over * 32);
					ent->pressure += ft_v2fmag(ft_v2fnorm(c[2], over * 32));
				}
			}
		}
	}
}

void	ft_entity_collisions(t_data *game, float dt)
{
	t_length	i;
	t_length	j;
	t_entity	*ent_1;
	t_entity	*ent_2;

	i = 0;
	while (i < game->map->active_nbr)
	{
		ent_1 = ft_vector_get(game->map->entities, i);
		j = 0;
		while (j < game->map->active_nbr)
		{
			if (i != j && ent_1->type > 0 && ent_1->radius > 0.0f)
			{
				ent_2 = ft_vector_get(game->map->entities, j);
				if (ent_2->radius > 0.0f)
					if (ft_is_overlap_circle(ent_1, ent_2))
						ft_resolve_collision_circle(ent_1, ent_2);
			}
			j++;
		}
		ft_resolve_collision_square(game, ent_1, dt);
		i++;
	}
}
