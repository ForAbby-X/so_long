/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tank_update.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:54:55 by alde-fre          #+#    #+#             */
/*   Updated: 2023/02/16 12:35:41 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	ft_damage_tank(t_data *game, t_entity *ent, int dam, float rot)
{
	t_dat_tank	*dat;

	dat = ent->data;
	ft_emmit_sparks(game, 6, ent->pos, rot);
	dat->health -= dam;
	if (dat->health <= 0.0f)
	{
		//ft_explosion(game, ent->pos, 80);
		ent->alive = 0;
		game->state = 3;
		game->state_time = 0.0f;
	}
}

static void	_ft_tank_update3(t_entity *s, t_dat_tank *dat, t_data *g)
{
	if (g->eng->mouse[1] && dat->fire_cool[0] >= 0.125f / 2)
	{
		ft_ent_add(g, ft_bullet_create(1, s->pos + ft_v2fr(dat->top_rot,
					35) + ft_v2fr(dat->top_rot - M_PI_2, 10), dat->top_rot
				+ ft_rand(-0.5f, 0.5f) * 0.20, s->uuid));
		dat->fire_cool[0] = 0.0f;
		g->shake -= ft_v2fr(dat->top_rot, 6);
	}
	if (g->eng->mouse[3] && dat->fire_cool[1] >= 4.0f)
	{
		ft_ent_add(g, ft_shell_create(s->pos
				+ ft_v2fr(dat->top_rot, 50), dat->top_rot));
		dat->fire_cool[1] = 0.0f;
		g->shake -= ft_v2fr(dat->top_rot, 80);
	}
}

static void	_ft_tank_update2(t_entity *s, t_dat_tank *dat, t_data *g, float dt)
{
	g->map->score += ft_v2fmag(dat->vel) * 32.0f * dt;
	dat = s->data;
	dat->bloody[0] = fmaxf(dat->bloody[0] - dt, 0.0f);
	dat->bloody[1] = fmaxf(dat->bloody[1] - dt, 0.0f);
	if (ft_check_col_zone(g->map->background, (t_v2i){s->pos[0],
			s->pos[1]} - ft_v2irot((t_v2i){0, 20}, s->rot),
			(t_color){0x64000C}, 5))
		dat->bloody[0] = 2.0f;
	if (ft_check_col_zone(g->map->background, (t_v2i){s->pos[0],
			s->pos[1]} + ft_v2irot((t_v2i){0, 20}, s->rot),
			(t_color){0x64000C}, 5))
		dat->bloody[1] = 2.0f;
	dat->top_rot = -atan2((g->cam.pos[0] + (int)g->eng->mouse_x)
			- s->pos[0], (g->cam.pos[1] + (int)g->eng->mouse_y)
			- s->pos[1]) + M_PI_2;
	_ft_tank_update3(s, dat, g);
}

void	ft_tank_update(t_entity *self, t_data *game, float dt)
{
	t_dat_tank	*dat;
	t_v2f		rolling;
	t_v2f		coef;

	dat = self->data;
	dat->fire_cool += (t_v2f){dt, dt};
	dat->timer += dt;
	if (game->eng->keys[XK_a])
		self->rot -= M_PI * dt * (1.0f - ft_v2fmag(dat->vel) / 15.5f);
	if (game->eng->keys[XK_d])
		self->rot += M_PI * dt * (1.0f - ft_v2fmag(dat->vel) / 15.5f);
	self->dir = ft_v2fr(self->rot, 1.0f);
	dat->trac = (t_v2f){0, 0};
	if (game->eng->keys[XK_w])
		dat->trac = self->dir * 90.0f;
	if (game->eng->keys[XK_s])
		dat->trac = -self->dir * 320.0f;
	dat->drag = -1.4257f * dat->vel * ft_v2fmag(dat->vel);
	rolling = -12.8f * dat->vel;
	coef = -60.4f * (1.0f - ft_v2fdot(self->dir, ft_v2fnorm(dat->vel, 1.0f)))
		* dat->vel;
	dat->acc = (dat->trac + dat->drag + rolling + coef) / 4.0f;
	dat->vel += dat->acc * dt;
	self->pos += dat->vel * 32.0f * dt;
	_ft_tank_update2(self, dat, game, dt);
}