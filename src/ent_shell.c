/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ent_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 19:18:32 by alde-fre          #+#    #+#             */
/*   Updated: 2023/01/08 12:02:01 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static int	_ft_shell_display(t_entity *self, t_data *game)
{
	t_dat_shell	*dat;
	int			anim;

	dat = self->data;
	anim = ((int)(dat->time * 10)) % 3;
	ft_put_sprite_r(game->eng, game->spr[16 + anim], ft_v2i(self->pos[0]
			- game->cam.pos[0], self->pos[1] - game->cam.pos[1]),
		ft_v2i(4, 4), self->rot);
	return (1);
}

static int	_ft_shell_update(t_entity *self, t_data *game, float dt)
{
	t_dat_shell	*dat;
	t_entity	*ent;
	t_length	i;

	dat = self->data;
	self->pos = self->pos + self->dir * dt;
	dat->time += dt;
	self->alive = !(dat->time >= 2.0f);
	i = 0;
	while (i < ft_vector_size(game->map->entities))
	{
		ent = ft_vector_get(game->map->entities, i);
		if (ent != self && ent->type == 2)
			if (ft_v2fmag(ent->pos - self->pos) < 15)
			{
				((t_dat_enn_base *)ent->data)->health = 0;
				break ;
			}
		i++;
	}
	return (1);
}

static int	_ft_shell_destroy(t_entity *self, t_data *game)
{
	(void)game;
	free((t_entity *)self->data);
	free((t_entity *)self);
	return (1);
}

t_entity	*ft_shell_create(t_v2f pos, float rot)
{
	t_entity	*ent;
	t_dat_shell	*data;

	ent = malloc(sizeof(t_entity));
	if (ent == NULL)
		return (NULL);
	data = malloc(sizeof(t_dat_shell));
	if (data == NULL)
		return (free(ent), NULL);
	data->time = 0.0f;
	ent->data = data;
	ent->display = &_ft_shell_display;
	ent->update = &_ft_shell_update;
	ent->destroy = &_ft_shell_destroy;
	ent->pos = pos;
	ent->dir = ft_v2fr(rot, 400);
	ent->rot = rot;
	ent->radius = 4;
	ent->uuid = ft_get_uuid();
	ent->type = -2;
	ent->alive = 1;
	return (ent);
}
