/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rambo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:27:25 by alde-fre          #+#    #+#             */
/*   Updated: 2024/06/28 11:50:16 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	_ft_rambo_display(t_entity *self, t_data *game)
{
	t_dat_rambo	*dat;
	int			anim;

	dat = self->data;
	anim = (int)(dat->timer * ft_v2fmag(self->dir) * 0.125f / 2);
	if (ft_v2fmag(self->dir) > 0.2f && ((anim) & 1))
	{
		ft_put_sprite_r(game->eng,
			game->spr[54 + ((anim / 2) & 1)],
			(t_rect){{self->pos[0] - game->cam.pos[0],
			self->pos[1] - game->cam.pos[1]},
		{10, 11}}, ft_vec_to_rad(self->dir));
	}
	ft_put_sprite_r(game->eng, game->spr[53], (t_rect){{self->pos[0]
		- game->cam.pos[0], self->pos[1] - game->cam.pos[1]},
	{10, 11}}, self->rot);
}

static void	_ft_rambo_destroy(t_entity *self, t_data *game)
{
	(void)game;
	free((t_entity *)self->data);
}

t_entity	ft_rambo_create(t_data *game, t_v2f pos)
{
	t_entity	ent;
	t_dat_rambo	*data;

	(void)game;
	ent = ft_ent_create(1, pos, (t_v2f){0, 0}, 13.0f);
	data = malloc(sizeof(t_dat_rambo));
	if (data == NULL)
		return ((t_entity){0});
	ft_memset(data, 0, sizeof(t_dat_rambo));
	data->health = 1000.0f;
	ent.data = data;
	ent.display = &_ft_rambo_display;
	ent.update = &ft_rambo_update;
	ent.destroy = &_ft_rambo_destroy;
	ent.rot = 0.0f;
	return (ent);
}
