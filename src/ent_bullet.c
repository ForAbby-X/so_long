/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ent_bullet.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:11:34 by alde-fre          #+#    #+#             */
/*   Updated: 2023/01/22 17:36:07 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static int	_ft_bullet_display(t_entity *self, t_data *game)
{
	t_dat_bullet	*dat;

	dat = self->data;
	ft_put_sprite_r(game->eng, game->spr[5 + dat->type], ft_v2i(self->pos[0]
			- game->cam.pos[0], self->pos[1] - game->cam.pos[1]),
		ft_v2i(28, 1), self->rot);
	return (1);
}

static int	_ft_bullet_update(t_entity *self, t_data *game, float dt)
{
	t_entity		*ent;
	t_length		i;
	t_dat_bullet	*dat;

	dat = self->data;
	self->pos = self->pos + self->dir * dt;
	dat->time += dt;
	self->alive = !(dat->time >= 2.0f);
	i = 0;
	while (i < game->map->active_nbr - 1)
	{
		ent = ft_vector_get(game->map->entities, i);
		if (ent->uuid != dat->shooter_id && ent->type > 0 && ent->type != 3
			&& ft_v2fmag(ent->pos - self->pos) < 11)
		{
			((t_dat_enn_base *)ent->data)->health -= ft_rand(15, 25);
			ft_emmit_blood(game, 10, self->pos, self->rot);
			ft_eng_sel_spr(game->eng, game->map->background);
			ft_put_sprite_r(game->eng, game->spr[23],
				(t_v2i){self->pos[0], self->pos[1]},
				(t_v2i){11, 13}, self->rot + ft_rand(-0.2f, 0.2f));
			ft_eng_sel_spr(game->eng, 0);
			self->alive = 0;
			break ;
		}
		i++;
	}
	if (ft_v2fmag(game->eplay->pos - self->pos) < 25 || ft_get_map(
			game->map, (t_v2i){floor(self->pos[0] / 32),
			floor(self->pos[1] / 32)}) == '1')
	{
		ft_emmit_sparks(game, 6, self->pos, self->rot + M_PI);
		self->alive = 0;
	}
	return (1);
}

static int	_ft_bullet_destroy(t_entity *self, t_data *game)
{
	(void)game;
	free((t_entity *)self->data);
	free((t_entity *)self);
	return (1);
}

t_entity	*ft_bullet_create(int type, t_v2f pos, float rot, t_uuid uuid)
{
	t_entity		*ent;
	t_dat_bullet	*data;

	ent = malloc(sizeof(t_entity));
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
	ent->pos = pos;
	ent->dir = ft_v2fr(rot, 1000);
	ent->rot = rot;
	ent->radius = 2.0f;
	ent->uuid = ft_get_uuid();
	ent->type = -1;
	ent->alive = 1;
	return (ent);
}
