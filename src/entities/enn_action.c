/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enn_action.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 14:13:06 by alde-fre          #+#    #+#             */
/*   Updated: 2024/06/28 11:55:10 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	ft_enn_state(t_data *g, t_entity *ent, t_dat_enn_base *dat, float dist)
{
	if (dat->state == 2 && dist < 230)
		dat->state = 2;
	else if (dist < 100)
		dat->state = 2;
	else if (dist < 200 && ft_cast_ray(g, ent->pos, g->eplay->pos))
		dat->state = 1;
	else if (dist < 350)
		dat->state = 0;
	else
		dat->state = 3;
	ent->rot = ft_vec_to_rad(g->eplay->pos - ent->pos);
	ent->dir = (t_v2f){0, 0};
	if (dat->state == 0)
		ent->dir = ft_v2fnorm(g->eplay->pos - ent->pos, 40.0f);
	else if (dat->state == 1)
	{
		if (dat->fire_cool >= 0.4f)
		{
			t_entity bullet = ft_bullet_create(dat->fire_cool = 0, ent->pos,
					ent->rot + ft_rand(-0.25f, 0.25f), ent->uuid);
			ft_ent_add(g, &bullet);
		}
	}
	else if (dat->state == 2)
		ent->dir = ft_v2fnorm(g->eplay->pos - ent->pos, -80.0f);
}

void	ft_damage_enn(t_data *game, t_entity *ent, float damage, float rot)
{
	t_dat_enn_base	*dat;

	dat = ent->data;
	dat->health -= damage;
	ft_emmit_blood(game, 10, ent->pos, rot);
	ft_eng_sel_spr(game->eng, game->map->background);
	ft_put_sprite_r(game->eng, game->spr[23],
		(t_rect){{ent->pos[0], ent->pos[1]}, {11, 13}}, rot
		+ ft_rand(-0.2f, 0.2f));
	ft_eng_sel_spr(game->eng, 0);
	if (dat->health <= 0.0f)
	{
		ft_emmit_pool_blood(game, 20, ent->pos);
		ft_eng_sel_spr(game->eng, game->map->background);
		ft_put_sprite_r(game->eng, game->spr[24],
			(t_rect){{ent->pos[0], ent->pos[1]}, {16, 14}}, ent->rot + M_PI);
		ft_put_sprite_r(game->eng, game->spr[15],
			(t_rect){{ent->pos[0], ent->pos[1]}, {16, 16}}, ent->rot + M_PI);
		ft_eng_sel_spr(game->eng, 0);
		ent->alive = 0;
	}
}
