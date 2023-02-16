/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enn_base.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:11:17 by alde-fre          #+#    #+#             */
/*   Updated: 2023/02/16 17:23:48 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	_ft_ennemy_display(t_entity *self, t_data *game)
{
	t_dat_enn_base	*dat;
	t_v2i			pos;
	int				anim;

	dat = self->data;
	pos = (t_v2i){self->pos[0] - game->cam.pos[0],
		self->pos[1] - game->cam.pos[1]};
	anim = ((int)(dat->fire_cool * 3) & 1);
	ft_put_sprite_r(game->eng, game->spr[7 + dat->state * 2 + anim],
		(t_rect){pos, {16, 16}}, self->rot);
}

static void	_ft_ennemy_update(t_entity *self, t_data *game, float dt)
{
	t_dat_enn_base	*dat;
	float			dist;

	dat = self->data;
	dist = ft_v2fmag(game->eplay->pos - self->pos);
	dat->fire_cool += dt;
	ft_enn_state(game, self, dat, dist);
	self->pos += self->dir * dt;
	if (game->eplay->type == 0 && (dist < 50 || self->pressure > 250.0f))
	{
		ft_damage_enn(game, self, dat->health, self->rot + M_PI);
		ft_paint_tank(game, game->eplay, self);
	}
}

static void	_ft_ennemy_destroy(t_entity *self, t_data *game)
{
	(void)game;
	free((t_entity *)self->data);
	free((t_entity *)self);
}

t_entity	*ft_ennemy_create(t_v2f pos, float rot)
{
	t_entity		*ent;
	t_dat_enn_base	*data;

	ent = ft_ent_create(2, pos, (t_v2f){0, 0}, 15.0f);
	if (ent == NULL)
		return (NULL);
	data = malloc(sizeof(t_dat_enn_base));
	if (data == NULL)
		return (free(ent), NULL);
	data->time = ft_rand(0.0f, 4.0f);
	data->health = 100.0f;
	data->max_health = 100.0f;
	data->fire_cool = 0.0f;
	data->state = 3;
	ent->data = data;
	ent->display = &_ft_ennemy_display;
	ent->update = &_ft_ennemy_update;
	ent->destroy = &_ft_ennemy_destroy;
	ent->rot = rot;
	return (ent);
}
