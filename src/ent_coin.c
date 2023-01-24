/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ent_coin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 18:06:42 by alde-fre          #+#    #+#             */
/*   Updated: 2023/01/23 17:36:28 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static int	_ft_coin_display(t_entity *self, t_data *game)
{
	t_dat_coin	*data;

	data = self->data;
	ft_put_sprite_r(game->eng, game->spr[31], (t_v2i){self->pos[0] \
		- game->cam.pos[0], self->pos[1] - game->cam.pos[1]}, \
		(t_v2i){16, 16}, self->rot);
	ft_put_sprite(game->eng, game->spr[32], (t_v2i){self->pos[0] - 6 \
		- game->cam.pos[0], self->pos[1] - (26 + sinf(data->time * 4) * 8) \
		- game->cam.pos[1]});
	return (1);
}

static int	_ft_coin_update(t_entity *self, t_data *game, float dt)
{
	t_dat_coin	*data;

	(void)self;
	(void)game;
	data = self->data;
	data->time += dt;
	if (ft_v2fmag(game->eplay->pos - self->pos) < 35.0f)
	{
		ft_eng_sel_spr(game->eng, game->map->background);
		ft_put_sprite_r(game->eng, game->spr[36],
			(t_v2i){self->pos[0], self->pos[1]},
			(t_v2i){16, 16}, self->rot);
		ft_eng_sel_spr(game->eng, NULL);
		self->alive = 0;
	}
	return (1);
}

static int	_ft_coin_destroy(t_entity *self, t_data *game)
{
	(void)game;
	free((t_entity *)self->data);
	free((t_entity *)self);
	return (1);
}

t_entity	*ft_coin_create(t_v2f pos)
{
	t_entity	*ent;
	t_dat_coin	*data;

	ent = malloc(sizeof(t_entity));
	if (ent == NULL)
		return (NULL);
	data = malloc(sizeof(t_dat_coin));
	if (data == NULL)
		return (free(ent), NULL);
	data->time = 0.0f;
	ent->data = data;
	ent->display = &_ft_coin_display;
	ent->update = &_ft_coin_update;
	ent->destroy = &_ft_coin_destroy;
	ent->pos = pos;
	ent->dir = (t_v2f){0, 0};
	ent->rot = ft_rand(0, M_PI_2);
	ent->radius = 10;
	ent->uuid = ft_get_uuid();
	ent->type = 3;
	ent->alive = 1;
	return (ent);
}
