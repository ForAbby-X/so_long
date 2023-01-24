/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ent_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 18:06:42 by alde-fre          #+#    #+#             */
/*   Updated: 2023/01/24 15:34:40 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static int	_ft_exit_count(t_object obj)
{
	t_entity	*ent;

	ent = obj;
	if (ent->type == 3)
		return (0);
	return (1);
}

static int	_ft_exit_display(t_entity *self, t_data *game)
{
	t_dat_exit	*data;

	(void)game;
	data = self->data;
	if (data->is_open)
		ft_put_sprite(game->eng, game->spr[34], (t_v2i){self->pos[0] - 64 \
		- game->cam.pos[0], self->pos[1] - 64 \
		- game->cam.pos[1]});
	return (1);
}

static int	_ft_exit_update(t_entity *self, t_data *game, float dt)
{
	t_dat_exit	*data;

	(void)self;
	(void)game;
	data = self->data;
	data->time += dt;
	data->is_open = !ft_vector_countif(game->map->entities, &_ft_exit_count);
	if (data->is_open && ft_v2fmag(game->eplay->pos - self->pos) < 50)
		game->state = 0;
	return (1);
}

static int	_ft_exit_destroy(t_entity *self, t_data *game)
{
	(void)game;
	free((t_entity *)self->data);
	free((t_entity *)self);
	return (1);
}

t_entity	*ft_exit_create(t_v2f pos)
{
	t_entity	*ent;
	t_dat_exit	*data;

	ent = malloc(sizeof(t_entity));
	if (ent == NULL)
		return (NULL);
	data = malloc(sizeof(t_dat_exit));
	if (data == NULL)
		return (free(ent), NULL);
	data->is_open = 0;
	data->time = 0.0f;
	ent->data = data;
	ent->display = &_ft_exit_display;
	ent->update = &_ft_exit_update;
	ent->destroy = &_ft_exit_destroy;
	ent->pos = pos;
	ent->dir = (t_v2f){0, 0};
	ent->rot = 0.0f;
	ent->radius = 14;
	ent->uuid = ft_get_uuid();
	ent->type = -1;
	ent->alive = 1;
	return (ent);
}