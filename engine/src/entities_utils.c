/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 18:34:41 by alde-fre          #+#    #+#             */
/*   Updated: 2022/11/28 18:58:35 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	ft_ent_check_activ(t_data *game)
{
	t_entity	*ent;
	t_v2i		center_pos;
	t_length	i;

	i = 0;
	while (i < game->map.active_nbr)
	{
		ent = (t_entity *)ft_vector_get(game->map.entities, i);
		center_pos = ft_v2isub(game->cam.pos, ft_v2idiv(game->cam.dim, 2));
		if (ft_v2fmag(ft_v2fsub(ent->pos, (t_v2f){center_pos.x, center_pos.y}))
		>= game->cam.dim.x + ent->radius)
		{
			printf("%p at %d is now inactive\n", ent, i);
			ft_vector_swap(game->map.entities, i, game->map.active_nbr - 1);
			game->map.active_nbr--;
		}
		i++;
	}
	while (i < ft_vector_size(game->map.entities))
	{
		ent = (t_entity *)ft_vector_get(game->map.entities, i);
		center_pos = ft_v2isub(game->cam.pos, ft_v2idiv(game->cam.dim, 2));
		if (ft_v2fmag(ft_v2fsub(ent->pos, (t_v2f){center_pos.x, center_pos.y}))
		< game->cam.dim.x + ent->radius)
		{
			printf("%p at %d is now active\n", ent, i);
			ft_vector_swap(game->map.entities, i, game->map.active_nbr);
			game->map.active_nbr++;
		}
		i++;
	}
}
