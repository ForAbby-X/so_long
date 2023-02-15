/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 18:34:41 by alde-fre          #+#    #+#             */
/*   Updated: 2023/02/04 16:31:59 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static int	_ft_is_active(t_data *game, t_entity *ent)
{
	t_v2i	center_pos;
	t_v2i	dist;

	center_pos = game->cam.pos + game->cam.dim / 2;
	dist = (t_v2i){ent->pos[0], ent->pos[1]} - center_pos;
	return (dist[0] * dist[0] + dist[1] * dist[1]
		< (game->cam.dim[0]) * (game->cam.dim[0]));
}

void	ft_ent_check_activ(t_data *game)
{
	t_entity	*ent;
	t_length	i;

	i = 0;
	while (i < game->map->active_nbr)
	{
		ent = (t_entity *)ft_vector_get(game->map->entities, i);
		if (!_ft_is_active(game, ent))
		{
			ft_vector_swap(game->map->entities, i, game->map->active_nbr - 1);
			game->map->active_nbr--;
		}
		i++;
	}
	while (i < ft_vector_size(game->map->entities))
	{
		ent = (t_entity *)ft_vector_get(game->map->entities, i);
		if (_ft_is_active(game, ent))
		{
			ft_vector_swap(game->map->entities, i, game->map->active_nbr);
			game->map->active_nbr++;
		}
		i++;
	}
}

int	ft_move_toward(t_v2f pos, t_v2f target, float speed, float r)
{
	t_v2f	diff;

	diff = pos - target;
	pos = pos + ft_v2fnorm(diff, speed);
	if (diff[0] * diff[0] + diff[1] * diff[1] < r * r)
		return (1);
	return (0);
}
