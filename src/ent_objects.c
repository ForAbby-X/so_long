/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ent_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:13:08 by alde-fre          #+#    #+#             */
/*   Updated: 2023/02/02 18:47:53 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	_ft_object_display(t_entity *self, t_data *game)
{
	t_dat_object	*dat;

	dat = self->data;
	ft_put_sprite_r(game->eng, game->spr[42 + dat->type], (t_rect){{self->pos[0]
		- game->cam.pos[0], self->pos[1] - game->cam.pos[1]},
	{14 + (dat->type == 3) * 2, 14 + (dat->type == 3) * 2}}, self->rot);
}

static void	_ft_object_update(t_entity *self, t_data *game, float dt)
{
	t_dat_object	*dat;

	(void)game;
	(void)dt;
	dat = self->data;
	if (ft_get_map(game->map, (t_v2i){self->pos[0], self->pos[1]} / 32) == '1'
		|| self->pressure > 1100.0f)
		dat->health = -10.0f;
	if (dat->health < 0.0f)
	{
		ft_eng_sel_spr(game->eng, game->map->background);
		ft_put_sprite_r(game->eng, game->spr[46 + dat->type],
			(t_rect){{self->pos[0], self->pos[1]},
			(t_v2i){14, 14} + (dat->type == 3) * 2}, self->rot);
		ft_eng_sel_spr(game->eng, NULL);
	}
	self->alive = (dat->health >= 0.0f);
}

static void	_ft_object_destroy(t_entity *self, t_data *game)
{
	(void)game;
	free((t_entity *)self->data);
	free((t_entity *)self);
}

t_entity	*ft_object_create(int type, t_v2f pos)
{
	t_entity		*ent;
	t_dat_object	*data;

	ent = malloc(sizeof(t_entity));
	if (ent == NULL)
		return (NULL);
	data = malloc(sizeof(t_dat_object));
	if (data == NULL)
		return (free(ent), NULL);
	data->type = type;
	data->health = ft_rand(175, 200) - (type == 3) * 50.0f;
	ent->data = data;
	ent->display = &_ft_object_display;
	ent->update = &_ft_object_update;
	ent->destroy = &_ft_object_destroy;
	ent->pos = pos + (t_v2f){ft_rand(-0.25, 0.25), ft_rand(-0.25, 0.25)};
	ent->dir = (t_v2f){0.0f, 0.0f};
	ent->rot = ft_rand(-M_PI, M_PI);
	ent->radius = 14.0f + (type == 3) * 2.0f;
	ent->uuid = ft_get_uuid();
	ent->type = 10;
	ent->alive = 1;
	return (ent);
}
