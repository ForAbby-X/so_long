/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ent_tank.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:27:25 by alde-fre          #+#    #+#             */
/*   Updated: 2023/01/28 18:38:25 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	_ft_tank_display(t_entity *self, t_data *game)
{
	t_dat_tank	*dat;

	dat = self->data;
	ft_put_sprite_r(game->eng, dat->spr, (t_v2i){self->pos[0]
		- game->cam.pos[0], self->pos[1] - game->cam.pos[1]},
		(t_v2i){33, 27}, self->rot);
	ft_put_sprite_r(game->eng, game->spr[1], (t_v2i){self->pos[0]
		- game->cam.pos[0], self->pos[1] - game->cam.pos[1]},
		(t_v2i){17, 15}, dat->top_rot);
	if (dat->timer >= 0.0625f)
	{
		ft_emmit_smoke_pipe(game, 2, ft_v2f(self->pos[0], self->pos[1])
			+ ft_v2fr(self->rot, -25));
		ft_eng_sel_spr(game->eng, game->map->background);
		ft_put_sprite_r(game->eng, game->spr[37 + (dat->bloody[0] > 0.0f)],
			(t_v2i){self->pos[0], self->pos[1]} - ft_v2irot((t_v2i){0, 20},
				self->rot), (t_v2i){5, 7}, self->rot);
		ft_put_sprite_r(game->eng, game->spr[37 + (dat->bloody[1] > 0.0f)],
			(t_v2i){self->pos[0], self->pos[1]} + ft_v2irot((t_v2i){0, 20},
				self->rot), (t_v2i){5, 7}, self->rot);
		ft_eng_sel_spr(game->eng, NULL);
		dat->timer -= 0.0625f;
	}
}

static void	_ft_tank_update2(t_entity *self, t_data *game, float dt)
{
	t_dat_tank	*dat;

	dat = self->data;
	dat->bloody[0] = fmaxf(dat->bloody[0] - dt, 0.0f);
	dat->bloody[1] = fmaxf(dat->bloody[1] - dt, 0.0f);
	if (ft_check_col_zone(game->map->background, (t_v2i){self->pos[0],
			self->pos[1]} - ft_v2irot((t_v2i){0, 20}, self->rot),
			(t_color){0x64000C}, 5))
		dat->bloody[0] = 2.0f;
	if (ft_check_col_zone(game->map->background, (t_v2i){self->pos[0],
			self->pos[1]} + ft_v2irot((t_v2i){0, 20}, self->rot),
			(t_color){0x64000C}, 5))
		dat->bloody[1] = 2.0f;
	dat->top_rot = -atan2((game->cam.pos[0] + (int)game->eng->mouse_x)
			- self->pos[0], (game->cam.pos[1] + (int)game->eng->mouse_y)
			- self->pos[1]) + M_PI_2;
	if (game->eng->mouse[1] && dat->fire_cool >= 0.125f / 2)
	{
		ft_ent_add(game, ft_bullet_create(1, self->pos + ft_v2fr(dat->top_rot,
					35) + ft_v2fr(dat->top_rot - M_PI_2, 10), dat->top_rot
				+ ft_rand(-0.5f, 0.5f) * 0.20, self->uuid));
		dat->fire_cool = 0.0f;
		game->shake = 1.0f;
	}
	if (game->eng->mouse[3] && dat->fire_cool >= 4.0f)
	{
		ft_ent_add(game, ft_shell_create(self->pos
				+ ft_v2fr(dat->top_rot, 50), dat->top_rot));
		dat->fire_cool = 0.0f;
		game->shake = 2.0f;
	}
}

static void	_ft_tank_update(t_entity *self, t_data *game, float dt)
{
	t_dat_tank	*dat;
	t_v2f		rolling;
	t_v2f		coef;

	dat = self->data;
	dat->fire_cool += dt;
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
	_ft_tank_update2(self, game, dt);
}

static void	_ft_tank_destroy(t_entity *self, t_data *game)
{
	ft_destroy_sprite(game->eng, ((t_dat_tank *)self->data)->spr);
	free((t_entity *)self->data);
	free((t_entity *)self);
}

t_entity	*ft_tank_create(t_data *game, t_v2f pos)
{
	t_entity	*ent;
	t_dat_tank	*data;

	ent = malloc(sizeof(t_entity));
	if (ent == NULL)
		return (NULL);
	data = malloc(sizeof(t_dat_tank));
	if (data == NULL)
		return (free(ent), NULL);
	data->spr = ft_cpy_sprite(game->eng, game->spr[0]);
	if (data->spr == NULL)
		return (free(data), free(ent), NULL);
	data->acc = (t_v2f){0, 0};
	data->vel = (t_v2f){0, 0};
	data->trac = (t_v2f){0, 0};
	data->drag = (t_v2f){0, 0};
	data->bloody = (t_v2i){0, 0};
	data->top_rot = 0.0f;
	data->fire_cool = 0.0f;
	data->timer = 0.0f;
	ent->data = data;
	ent->display = &_ft_tank_display;
	ent->update = &_ft_tank_update;
	ent->destroy = &_ft_tank_destroy;
	ent->pos = pos;
	ent->dir = (t_v2f){0, 0};
	ent->rot = M_PI_4;
	ent->radius = 31.0f;
	ent->uuid = ft_get_uuid();
	ent->type = 0;
	ent->alive = 1;
	return (ent);
}
