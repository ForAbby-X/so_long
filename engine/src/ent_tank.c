/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ent_tank.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:27:25 by alde-fre          #+#    #+#             */
/*   Updated: 2022/11/25 09:33:36 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static int	_ft_tank_display(t_entity *self, t_data *game)
{
	t_length	i;
	t_dat_tank	*dat;

	dat = self->data;
	i = 0;
	while (i < 10)
	{
		ft_put_sprite_r(game->eng, dat->spr, ft_v2i(self->pos.x -
				game->cam.pos.x, self->pos.y - game->cam.pos.y - i),
			ft_v2i(33, 27), self->rot);
		i++;
	}
	i = 0;
	while (i < 3)
	{
		ft_put_sprite_r(game->eng, game->spr[1], ft_v2i(self->pos.x -
				game->cam.pos.x, self->pos.y - game->cam.pos.y - 10 - i),
			ft_v2i(17, 15), dat->top_rot);
		i++;
	}
	if (dat->timer >= 0.0625f)
	{
		ft_emmit_smoke_pipe(game, 2, ft_v2fadd(
				ft_v2f(self->pos.x, self->pos.y - 10),
				ft_v2fr(self->rot, -25)));
		dat->timer -= 0.0625f;
	}
	ft_circle(game->eng, ft_v2i(self->pos.x -
		game->cam.pos.x, self->pos.y - game->cam.pos.y), 100, ft_color_d(0x0F0000));
	ft_circle(game->eng, ft_v2i(self->pos.x -
		game->cam.pos.x, self->pos.y - game->cam.pos.y), 175, ft_color_d(0x000F00));
	ft_circle(game->eng, ft_v2i(self->pos.x -
		game->cam.pos.x, self->pos.y - game->cam.pos.y), 300, ft_color_d(0x00000F));
	ft_circle(game->eng, ft_v2i(self->pos.x -
		game->cam.pos.x, self->pos.y - game->cam.pos.y), 55, ft_color_d(0x8E0000));
	return (1);
}

static void	_ft_tank_update2(t_entity *self, t_data *game, float dt)
{
	t_dat_tank	*dat;

	dat = self->data;
	dat->acc = sinf(fabsf(ft_v2fdot(self->dir, dat->ine)) * M_PI_2);
	dat->vel = dat->vel * 0.96f * (dat->acc * dat->acc);
	dat->vel = ft_min(120, ft_max(-100, dat->vel));
	self->pos = ft_v2fadd(self->pos, ft_v2fmul(dat->ine, dat->vel * dt));
	dat->top_rot = -atan2((game->cam.pos.x + (int)game->eng->mouse_x)
			- self->pos.x,
			(game->cam.pos.y + (int)game->eng->mouse_y) - self->pos.y + 12)
		+ M_PI_2;
	if (game->eng->mouse[1] && dat->fire_cool >= 0.125f / 2)
	{
		ft_ent_add(game, ft_bullet_create(1,
				ft_v2fadd(self->pos, ft_v2fadd(ft_v2fr(dat->top_rot, 35),
						ft_v2fr(dat->top_rot - M_PI_2, 10))),
				dat->top_rot + ft_rand(-0.5f, 0.5f) * 0.20, self->uuid));
		dat->fire_cool = 0.0f;
		game->shake = 1.0f;
	}
	if (game->eng->mouse[3] && dat->fire_cool >= 4.0f)
	{
		ft_ent_add(game, ft_shell_create(ft_v2fadd(self->pos,
					ft_v2fr(dat->top_rot, 50)), dat->top_rot));
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
		dat->ine = ft_v2fmul(self->dir, -1);
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
	data->ine = (t_v2f){0, 0};
	data->acc = 0.0f;
	data->vel = 0.0f;
	data->top_rot = 0.0f;
	data->fire_cool = 0.0f;
	data->timer = 0.0f;
	data->spr = ft_cpy_sprite(game->eng, game->spr[0]);
	ent->data = data;
	ent->display = &_ft_tank_display;
	ent->update = &_ft_tank_update;
	ent->destroy = &_ft_tank_destroy;
	ent->pos = pos;
	ent->dir = (t_v2f){0, 0};
	ent->rot = 0.0f;
	ent->radius = 37.0f;
	ent->uuid = ft_get_uuid();
	ent->type = 0;
	ent->alive = 1;
	return (ent);
}
