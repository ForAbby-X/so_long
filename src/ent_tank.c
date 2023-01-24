/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ent_tank.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:27:25 by alde-fre          #+#    #+#             */
/*   Updated: 2023/01/18 14:32:14 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static int	_ft_tank_display(t_entity *self, t_data *game)
{
	t_dat_tank	*dat;

	dat = self->data;
	ft_put_sprite_r(game->eng, dat->spr, ft_v2i(self->pos[0]
			- game->cam.pos[0], self->pos[1] - game->cam.pos[1]),
		ft_v2i(33, 27), self->rot);
	ft_put_sprite_r(game->eng, game->spr[1], ft_v2i(self->pos[0]
			- game->cam.pos[0], self->pos[1] - game->cam.pos[1]),
		ft_v2i(17, 15), dat->top_rot);
	if (dat->timer >= 0.0625f)
	{
		ft_emmit_smoke_pipe(game, 2, ft_v2f(self->pos[0], self->pos[1])
			+ ft_v2fr(self->rot, -25));
		ft_eng_sel_spr(game->eng, game->map->background);
		ft_circle(game->eng, (t_v2i){self->pos[0], self->pos[1]}
			+ ft_v2irot((t_v2i){-20, 0}, self->rot - M_PI_2), 6, ft_color_d(0));
		ft_circle(game->eng, (t_v2i){self->pos[0], self->pos[1]}
			+ ft_v2irot((t_v2i){20, 0}, self->rot - M_PI_2), 6, ft_color_d(0));
		ft_eng_sel_spr(game->eng, NULL);
		dat->timer -= 0.0625f;
	}
	return (1);
}

static void	_ft_tank_update2(t_entity *self, t_data *game, float dt)
{
	t_dat_tank	*dat;

	dat = self->data;
	dat->acc = sinf(fabsf(ft_v2fdot(self->dir, dat->ine)) * M_PI_2);
	dat->vel = dat->vel * 0.96f * (dat->acc * dat->acc);
	dat->vel = ft_min(120, ft_max(-100, dat->vel));
	self->pos = self->pos + dat->ine * dat->vel * dt;
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

static int	_ft_tank_update(t_entity *self, t_data *game, float dt)
{
	t_dat_tank	*dat;

	dat = self->data;
	dat->fire_cool += dt;
	dat->timer += dt;
	if (game->eng->keys[XK_a])
		self->rot -= M_PI * dt * (1.0f - dat->vel / 150.0f);
	if (game->eng->keys[XK_d])
		self->rot += M_PI * dt * (1.0f - dat->vel / 150.0f);
	self->dir = ft_v2fr(self->rot, 1.0f);
	if (game->eng->keys[XK_w])
	{
		dat->ine = ft_v2fmul(self->dir, 1);
		dat->vel += 8.0f;
	}
	if (game->eng->keys[XK_s])
	{
		dat->ine = -self->dir;
		dat->vel += 3.0f;
	}
	_ft_tank_update2(self, game, dt);
	return (1);
}

static int	_ft_tank_destroy(t_entity *self, t_data *game)
{
	ft_destroy_sprite(game->eng, ((t_dat_tank *)self->data)->spr);
	free((t_entity *)self->data);
	free((t_entity *)self);
	return (1);
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
	data->ine = (t_v2f){0, 0};
	data->acc = 0.0f;
	data->vel = 0.0f;
	data->top_rot = 0.0f;
	data->fire_cool = 0.0f;
	data->timer = 0.0f;
	ent->data = data;
	ent->display = &_ft_tank_display;
	ent->update = &_ft_tank_update;
	ent->destroy = &_ft_tank_destroy;
	ent->pos = pos;
	ent->dir = (t_v2f){0, 0};
	ent->rot = M_PI_2 / 2;
	ent->radius = 31.0f;
	ent->uuid = ft_get_uuid();
	ent->type = 0;
	ent->alive = 1;
	return (ent);
}
