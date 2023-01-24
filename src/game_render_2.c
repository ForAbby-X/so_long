/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_render_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:11:26 by alde-fre          #+#    #+#             */
/*   Updated: 2022/12/23 19:38:45 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	ft_game_all_par(t_data *data, float dt)
{
	t_length	i;
	t_particle	*par;

	i = 0;
	while (i < ft_vector_size(data->map->particles))
	{
		par = (t_particle *)ft_vector_get(data->map->particles, i);
		par->pos = par->pos + par->dir * dt;
		par->time += dt;
		ft_put_sprite(data->eng, par->spr,
			(t_v2i){par->pos[0] - data->cam.pos[0],
			par->pos[1] - data->cam.pos[1]} - par->off);
		if (par->time >= par->life_time)
		{
			free(par);
			ft_vector_rem(data->map->particles, i);
		}
		else
			i++;
	}
	return (1);
}
