/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rambo_update.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:27:25 by alde-fre          #+#    #+#             */
/*   Updated: 2023/02/21 11:08:31 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	ft_damage_rambo(t_data *game, t_entity *ent, float damage, float rot)
{
	t_dat_rambo	*dat;

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
		game->map->bullet_time = 0.0f;
		ft_emmit_pool_blood(game, 20, ent->pos);
		ft_eng_sel_spr(game->eng, game->map->background);
		ft_put_sprite_r(game->eng, game->spr[24],
			(t_rect){{ent->pos[0], ent->pos[1]}, {16, 14}}, ent->rot + M_PI);
		ft_put_sprite_r(game->eng, game->spr[58],
			(t_rect){{ent->pos[0], ent->pos[1]}, {16, 16}}, ent->rot + M_PI);
		ft_eng_sel_spr(game->eng, 0);
		ent->alive = 0;
		game->is_finished = 1;
	}
}

static void	ft_rambo_update_2(t_entity *self, t_dat_rambo *dat,
	t_data *game, float dt)
{
	self->rot = -atan2((game->cam.pos[0] + (int)game->eng->mouse_x)
			- self->pos[0], (game->cam.pos[1] + (int)game->eng->mouse_y)
			- self->pos[1]) + M_PI_2;
	if (dat->fire_cool[0] >= 0.03125f)
	{
		ft_ent_add(game, ft_bullet_create(1, self->pos + ft_v2fr(self->rot,
					19) + ft_v2fr(self->rot + M_PI_2, 5), self->rot
				+ ft_rand(-0.5f, 0.5f) * 0.20, self->uuid));
		game->shake -= ft_v2fr(self->rot, 3);
		dat->fire_cool[0] -= 0.03125f;
	}
	self->pos += self->dir * dt;
	game->score += ft_v2fmag(self->dir) * dt;
}

void	ft_rambo_update(t_entity *self, t_data *game, float dt)
{
	t_dat_rambo	*dat;

	dat = self->data;
	dat->timer += dt;
	if (game->eng->mouse[1])
		dat->fire_cool[0] += dt;
	else
		dat->fire_cool[0] = fmaxf(dat->fire_cool[0] - dt, -1.0f);
	self->dir = (t_v2f){0.0f, 0.0f};
	if (game->eng->keys[XK_a])
		self->dir += (t_v2f){-1.0f, 0.0f};
	if (game->eng->keys[XK_d])
		self->dir += (t_v2f){1.0f, 0.0f};
	if (game->eng->keys[XK_w])
		self->dir += (t_v2f){0.0f, -1.0f};
	if (game->eng->keys[XK_s])
		self->dir += (t_v2f){0.0f, 1.0f};
	self->dir = ft_v2fnorm(self->dir, 140.0f
			* fmaxf(fminf(-dat->fire_cool[0], 1.0f), 0.5f));
	ft_rambo_update_2(self, dat, game, dt);
}
