/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ent_enn_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:11:17 by alde-fre          #+#    #+#             */
/*   Updated: 2022/11/28 18:54:26 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static int	_ft_ennemy_display(t_entity *self, t_data *game)
{
	t_dat_enn_base	*dat;
	t_v2i			pos;
	int				anim;

	dat = self->data;
	pos = ft_v2i(self->pos.x - game->cam.pos.x, self->pos.y - game->cam.pos.y);
	anim = ((int)(dat->fire_cool * 3) & 1);
	ft_put_sprite_r(game->eng, game->spr[7 + dat->state * 2 + anim],
		pos, ft_v2i(16, 16), self->rot);
	ft_rect(game->eng, ft_v2iadd(pos, ft_v2i(-16, 18)),
		ft_v2i((float)dat->health / dat->max_health * 32, 3),
		ft_color_inter(ft_color_d(0x008F00), ft_color_d(0x8F0000),
			dat->health / dat->max_health));
	return (1);
}

static int	_ft_ennemy_update(t_entity *self, t_data *game, float dt)
{
	t_dat_enn_base	*dat;
	float			dist;

	dat = self->data;
	dist = ft_v2fmag(ft_v2fsub(game->eplay->pos, self->pos));
	dat->fire_cool += dt;
	if (dat->state == 2 && dist < 230)
		dat->state = 2;
	else if (dist < 100)
		dat->state = 2;
	else if (dist < 175)
		dat->state = 1;
	else if (dist < 300)
		dat->state = 0;
	else
		dat->state = 3;
	self->rot = -atan2(-ft_v2fsub(game->eplay->pos, self->pos).y,
			ft_v2fsub(game->eplay->pos, self->pos).x);
	if (dat->state == 0)
		self->dir = ft_v2fnorm(ft_v2fsub(game->eplay->pos, self->pos), 40.0f);
	else if (dat->state == 1)
	{
		self->dir = (t_v2f){0.0f, 0.0f};
		if (dat->fire_cool >= 0.4f)
		{
			//ft_ent_add(game, ft_bullet_create(0, self->pos, self->rot
			//		+ ft_rand(-0.25f, 0.25f), self->uuid));
			dat->fire_cool = 0;
		}
	}
	else if (dat->state == 2)
		self->dir = ft_v2fnorm(ft_v2fsub(game->eplay->pos, self->pos), -80.0f);
	else
		self->dir = ft_v2f(0, 0);
	self->pos = ft_v2fadd(self->pos, ft_v2fmul(self->dir, dt));
	if (ft_v2fmag(ft_v2fsub(game->eplay->pos, self->pos)) < 50)
	{
		dat->health = 0.0f;
		ft_emmit_blood(game, 60, self->pos, self->rot + M_PI);
		ft_paint_tank(game, game->eplay, self);
	}
	if (dat->health <= 0.0f)
	{
		ft_emmit_pool_blood(game, 20, self->pos);
		ft_eng_sel_spr(game->eng, game->map.background);
		ft_put_sprite_r(game->eng, game->spr[24],
			ft_v2i(self->pos.x, self->pos.y),
			ft_v2i(16, 14), self->rot + M_PI);
		ft_put_sprite_r(game->eng, game->spr[15],
			ft_v2i(self->pos.x, self->pos.y),
			ft_v2i(16, 16), self->rot + M_PI);
		ft_eng_sel_spr(game->eng, 0);
		self->alive = 0;
	}
	return (1);
}

static int	_ft_ennemy_destroy(t_entity *self, t_data *game)
{
	(void)game;
	free((t_entity *)self->data);
	free((t_entity *)self);
	return (1);
}

t_entity	*ft_ennemy_create(t_v2f pos, float rot)
{
	t_entity		*ent;
	t_dat_enn_base	*data;

	ent = malloc(sizeof(t_entity));
	if (ent == NULL)
		return (NULL);
	data = malloc(sizeof(t_dat_enn_base));
	if (data == NULL)
		return (free(ent), NULL);
	data->time = 0.0f;
	data->health = 100.0f;
	data->max_health = 100.0f;
	data->fire_cool = 0.0f;
	data->state = 3;
	ent->data = data;
	ent->display = &_ft_ennemy_display;
	ent->update = &_ft_ennemy_update;
	ent->destroy = &_ft_ennemy_destroy;
	ent->pos = pos;
	ent->dir = (t_v2f){0, 0};
	ent->rot = rot;
	ent->radius = 16;
	ent->uuid = ft_get_uuid();
	ent->type = 2;
	ent->alive = 1;
	return (ent);
}
