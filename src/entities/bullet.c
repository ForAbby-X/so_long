/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bullet.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:11:34 by alde-fre          #+#    #+#             */
/*   Updated: 2023/02/16 16:11:56 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	_ft_bullet_display(t_entity *self, t_data *game)
{
	t_dat_bullet	*dat;

	dat = self->data;
	ft_put_sprite_r(game->eng, game->spr[5 + dat->type], (t_rect){{self->pos[0]
		- game->cam.pos[0], self->pos[1] - game->cam.pos[1]},
	{28, 1}}, self->rot);
}

static void	_ft_bullet_update(t_entity *self, t_data *game, float dt)
{
	t_entity		*ent;
	t_length		i;
	t_dat_bullet	*dat;

	dat = self->data;
	self->alive = !(dat->time >= 2.0f);
	i = -1;
	while (++i < game->map->active_nbr - 1 && self->alive)
	{
		ent = ft_vector_get(game->map->entities, i);
		if (ent->uuid != dat->shooter_id && ent->type >= 0 && ent->type != 3
			&& ft_v2fmag(ent->pos - self->pos) < ent->radius)
			if (ft_damage_ent(game, ent, ft_rand(15, 25), self->rot))
				self->alive = 0;
	}
	if (ft_get_map(game->map, (t_v2i){floor(self->pos[0] / 32),
			floor(self->pos[1] / 32)}) == '1')
	{
		ft_emmit_sparks(game, 6, self->pos, self->rot + M_PI);
		self->alive = 0;
	}
	dat->time += dt;
	self->pos = self->pos + self->dir * dt;
}

static void	_ft_bullet_destroy(t_entity *self, t_data *game)
{
	(void)game;
	free((t_entity *)self->data);
	free((t_entity *)self);
}

t_entity	*ft_bullet_create(int type, t_v2f pos, float rot, t_uuid uuid)
{
	t_entity		*ent;
	t_dat_bullet	*data;

	ent = ft_ent_create(-1, pos, ft_v2fr(rot, 1000), 0.0f);
	if (ent == NULL)
		return (NULL);
	data = malloc(sizeof(t_dat_bullet));
	if (data == NULL)
		return (free(ent), NULL);
	data->type = type;
	data->time = 0.0f;
	data->shooter_id = uuid;
	ent->data = data;
	ent->display = &_ft_bullet_display;
	ent->update = &_ft_bullet_update;
	ent->destroy = &_ft_bullet_destroy;
	ent->rot = rot;
	return (ent);
}
