/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 18:34:41 by alde-fre          #+#    #+#             */
/*   Updated: 2024/06/28 16:44:24 by alde-fre         ###   ########.fr       */
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
		ent = ft_ent_get(game, i);
		if (!_ft_is_active(game, ent))
		{
			if (game->pindex == game->map->active_nbr - 1)
				game->pindex = i;
			else if (game->pindex == i)
				game->pindex = game->map->active_nbr - 1;

			t_entity tmp = *ft_ent_get(game, i);
			*ft_ent_get(game, i) = *ft_ent_get(game, game->map->active_nbr - 1);
			*ft_ent_get(game, game->map->active_nbr - 1) = tmp;
			game->map->active_nbr--;
		}
		i++;
	}
	while (i < vector_size(&game->map->entities))
	{
		ent = ft_ent_get(game, i);
		if (_ft_is_active(game, ent))
		{
			if (game->pindex == i)
				game->pindex = game->map->active_nbr;
			else if (game->pindex == game->map->active_nbr)
				game->pindex = i;

			t_entity tmp = *ft_ent_get(game, i);
			*ft_ent_get(game, i) = *ft_ent_get(game, game->map->active_nbr);
			*ft_ent_get(game, game->map->active_nbr) = tmp;
			game->map->active_nbr++;
		}
		i++;
	}
	game->eplay = ft_ent_get(game, game->pindex);
	game->rplay = game->eplay->data;
	game->tplay = game->eplay->data;
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

int	ft_damage_ent(t_data *game, t_entity *ent, int dam, float rot)
{
	if (ent->type == 2)
		ft_damage_enn(game, ent, dam, rot);
	else if (ent->type == 10)
		ft_damage_object(game, ent, dam, rot);
	else if (ent->type == 0)
		ft_damage_tank(game, ent, dam, rot);
	else if (ent->type == 1)
		ft_damage_rambo(game, ent, dam, rot);
	else
		return (0);
	return (1);
}
