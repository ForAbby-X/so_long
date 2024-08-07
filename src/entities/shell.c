/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 19:18:32 by alde-fre          #+#    #+#             */
/*   Updated: 2024/06/28 11:55:40 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	_ft_shell_display(t_entity *self, t_data *game)
{
	t_dat_shell	*dat;
	int			anim;

	dat = self->data;
	anim = ((int)(dat->time * 10)) % 3;
	ft_put_sprite_r(game->eng, game->spr[16 + anim], (t_rect){{self->pos[0]
		- game->cam.pos[0], self->pos[1] - game->cam.pos[1]}, {4, 4}},
		self->rot);
}

static void	_ft_shell_update(t_entity *self, t_data *game, float dt)
{
	t_entity	*ent;
	t_length	i;

	((t_dat_shell *)self->data)->time += dt;
	self->alive = !(((t_dat_shell *)self->data)->time >= 2.0f);
	if (ft_get_map(game->map, (t_v2i){self->pos[0], self->pos[1]} / 32) == '1')
	{
		self->alive = 0;
		game->map->bullet_time = 0.0f;
		ft_explosion(game, self->pos - self->dir * dt * 2, 64);
	}
	i = -1;
	while (self->alive && ++i < game->map->active_nbr)
	{
		ent = vector_get(&game->map->entities, i);
		if (((ent != self && (ent->type == 2 || ent->type == 10)
					&& ft_v2fmag(ent->pos - self->pos) < ent->radius)))
		{
			self->alive = 0;
			game->map->bullet_time = 0.0f;
			ft_explosion(game, ent->pos, 64);
		}
	}
	self->pos += self->dir * dt;
}

static void	_ft_shell_destroy(t_entity *self, t_data *game)
{
	(void)game;
	free((t_entity *)self->data);
}

t_entity	ft_shell_create(t_v2f pos, float rot)
{
	t_entity	ent;
	t_dat_shell	*data;

	ent = ft_ent_create(-2, pos, ft_v2fr(rot, 400), 0.0f);
	data = malloc(sizeof(t_dat_shell));
	if (data == NULL)
		return ((t_entity){0});
	data->time = 0.0f;
	ent.data = data;
	ent.display = &_ft_shell_display;
	ent.update = &_ft_shell_update;
	ent.destroy = &_ft_shell_destroy;
	ent.rot = rot;
	return (ent);
}
