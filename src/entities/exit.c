/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 18:06:42 by alde-fre          #+#    #+#             */
/*   Updated: 2023/02/25 15:06:14 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	ft_exit_count(t_object obj)
{
	t_entity	*ent;

	ent = obj;
	if (ent->type == 8)
		return (0);
	return (1);
}

static void	_ft_exit_display(t_entity *self, t_data *game)
{
	t_dat_exit	*data;
	float		s;

	(void)game;
	data = self->data;
	if (data->is_open)
	{
		s = sinf(game->time);
		ft_put_sprite_r(game->eng, game->spr[34], (t_rect){{self->pos[0]
			- game->cam.pos[0], self->pos[1] - game->cam.pos[1] - 60}, {14, 0}},
			s * M_PI / 10.0f);
	}
}

static void	_ft_exit_update(t_entity *self, t_data *game, float dt)
{
	t_dat_exit	*data;

	data = self->data;
	data->time += dt;
	data->is_open = !ft_vector_countif(game->map->entities, &ft_exit_count);
	if (!game->is_finished
		&& data->is_open && ft_v2fmag(game->eplay->pos - self->pos)
		< game->eplay->radius + 4)
	{
		game->state = 4;
		game->state_time = 0.0f;
	}
}

static void	_ft_exit_destroy(t_entity *self, t_data *game)
{
	(void)game;
	free((t_entity *)self->data);
	free((t_entity *)self);
}

t_entity	*ft_exit_create(t_v2f pos)
{
	t_entity	*ent;
	t_dat_exit	*data;

	ent = ft_ent_create(-3, pos, (t_v2f){0, 0}, 0.0f);
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
	ent->rot = 0.0f;
	return (ent);
}
