/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ent_bullet.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:11:34 by alde-fre          #+#    #+#             */
/*   Updated: 2022/11/23 16:50:25 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static int	_ft_bullet_display(t_entity *self, t_data *game)
{
	t_dat_bullet	*dat;

	dat = self->data;
	ft_put_sprite_r(game->eng, game->spr[5 + dat->type], ft_v2i(dat->pos.x -
		game->cam.pos.x, dat->pos.y - game->cam.pos.y - 11),
		ft_v2i(28, 1), dat->rot);
	return (1);
}

static int	_ft_bullet_update(t_entity *self, t_data *game, float dt)
{
	(void)game;
	t_entity		*ent;
	t_length		i;
	t_dat_bullet	*dat;

	dat = self->data;
	dat->pos = ft_v2fadd(dat->pos, ft_v2fmul(dat->dir, dt));
	dat->time += dt;
	self->alive = !(dat->time >= 2.0f);
	i = 0;
	while (i < ft_vector_size(game->map.entities))
	{
		ent = ft_vector_get(game->map.entities, i);
		if (ent != self && ent->type == 2 && ((t_dat_enn_base *)ent->data)->state != 4)
			if (ft_v2fmag(ft_v2fsub(((t_dat_enn_base *)ent->data)->pos, dat->pos)) < 11)
			{
				((t_dat_enn_base *)ent->data)->health -= 15.0f +
					((float)rand() / RAND_MAX * 10.0f);
				ft_emmit_blood(game, 10, dat->pos, dat->rot);
				ft_eng_sel_spr(game->eng, game->map.background);
				ft_put_sprite_r(game->eng, game->spr[23],
					ft_v2i(dat->pos.x, dat->pos.y),
					ft_v2i(11, 13), dat->rot + ft_rand(-0.2f, 0.2f));
				ft_eng_sel_spr(game->eng, 0);
				self->alive = 0;
				break ;
			}
		i++;
	}
	if (ft_v2fmag(ft_v2fsub(game->player->pos, dat->pos)) < 25 || ft_get_map(
		&game->map, ft_v2i(floor(dat->pos.x / 32), floor(dat->pos.y / 32))) == 1)
		{
			ft_emmit_sparks(game, 6, dat->pos, dat->rot + M_PI);
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

t_entity	*ft_bullet_create(t_data *game, int type, t_v2f pos, float rot)
{
	(void)game;
	t_entity		*ent;
	t_dat_bullet	*data;

	ent = malloc(sizeof(t_entity));
	data = malloc(sizeof(t_dat_bullet));
	data->pos = pos;
	data->dir = ft_v2fr(rot, 1000);
	data->type = type;
	data->rot = rot;
	data->time = 0.0f;
	ent->data = data;
	ent->display = &_ft_bullet_display;
	ent->update = &_ft_bullet_update;
	ent->destroy = &_ft_bullet_destroy;
	ent->type = -1;
	ent->alive = 1;
    return (ent);
}
