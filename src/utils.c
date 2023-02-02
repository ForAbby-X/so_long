/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 13:43:43 by alde-fre          #+#    #+#             */
/*   Updated: 2023/02/02 14:49:23 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	ft_check_col(t_color a, t_color b, int diff)
{
	int	col[3];

	col[0] = ((int)(a.d >> 16) & 0xFF) - ((int)(b.d >> 16) & 0xFF);
	col[1] = ((int)(a.d >> 8) & 0xFF) - ((int)(b.d >> 8) & 0xFF);
	col[2] = ((int)(a.d) & 0xFF) - ((b.d) & 0xFF);
	if ((col[0] >= diff || col[0] < -diff)
		|| (col[1] >= diff || col[1] < -diff)
		|| (col[2] >= diff || col[2] < -diff))
		return (0);
	return (1);
}

int	ft_check_col_zone(t_sprite *spr, t_v2i pos, t_color b, int diff)
{
	t_v2i	xy;

	xy[1] = pos[1] - 5;
	while (xy[1] < pos[1] + 5)
	{
		xy[0] = pos[0] - 5;
		while (xy[0] < pos[0] + 5)
		{
			if (ft_check_col(ft_get_color(spr, xy), b, diff))
				return (1);
			xy[0]++;
		}
		xy[1]++;
	}
	return (0);
}

int	ft_get_obj_prob(t_map *map, t_v2i pos)
{
	int		count;
	t_v2i	xy;

	count = 0;
	xy[1] = pos[1] - 2;
	while (xy[1] < pos[1] + 2)
	{
		xy[0] = pos[0] - 2;
		while (xy[0] < pos[0] + 2)
		{
			if (ft_get_map(map, xy) == '1')
				count++;
			xy[0]++;
		}
		xy[1]++;
	}
	return (count);
}

void	ft_explosion(t_data *game, t_v2f pos, float power)
{
	t_length	i;
	t_entity	*ent;
	float		damage;
	t_v2f		diff;

	ft_emmit_explosion(game, pos, power);
	ft_eng_sel_spr(game->eng, game->map->background);
	ft_put_sprite_r(game->eng, game->spr[40], (t_rect){{pos[0], pos[1]},
	{64, 64}}, ft_rand(-M_PI, M_PI));
	ft_eng_sel_spr(game->eng, NULL);
	i = 0;
	while (i < game->map->active_nbr)
	{
		ent = ft_vector_get(game->map->entities, i);
		i++;
		diff = ent->pos - pos;
		damage = fminf(fmaxf(ft_v2fmag(diff), 0.0f), 180.0f) / 1.4f / 128.0f;
		damage = (1.0f - (damage * damage * damage)) * 110.0f;
		if (damage < 0.5f || ft_cast_ray(game, pos, ent->pos) == 0)
			continue ;
		if (ent->type == 2)
			ft_damage_enn(game, ent, damage, atan2f(diff[1], diff[0]));
		if (ent->type == 10)
			((t_dat_object *)ent->data)->health -= damage;
	}
}
