/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rambo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:27:25 by alde-fre          #+#    #+#             */
/*   Updated: 2023/02/16 18:42:12 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	_ft_rambo_display(t_entity *self, t_data *game)
{
	t_dat_rambo	*dat;

	dat = self->data;
	if (ft_v2fmag(self->dir) > 0.2f)
	{
		ft_put_sprite_r(game->eng,
			game->spr[54 + (((int)(dat->timer * 4)) & 1)],
			(t_rect){{self->pos[0] - game->cam.pos[0],
			self->pos[1] - game->cam.pos[1]},
		{10, 11}}, ft_vec_to_rad(self->dir));
	}
	ft_put_sprite_r(game->eng, game->spr[53], (t_rect){{self->pos[0]
		- game->cam.pos[0], self->pos[1] - game->cam.pos[1]},
	{10, 11}}, self->rot);
}

static void	_ft_rambo_update(t_entity *self, t_data *game, float dt)
{
	t_dat_rambo	*dat;

	dat = self->data;
	dat->timer += dt;
	if (game->eng->mouse[1])
		dat->fire_cool[0] += dt;
	else
		dat->fire_cool[0] = fmaxf(dat->fire_cool[0] - dt, -1.0f);
	self->dir = (t_v2f){0.0f, 0.0f};
	if (game->eng->keys[XK_a])
		self->dir += (t_v2f){-1.0f, 0.0f};
	if (game->eng->keys[XK_d])
		self->dir += (t_v2f){1.0f, 0.0f};
	if (game->eng->keys[XK_w])
		self->dir += (t_v2f){0.0f, -1.0f};
	if (game->eng->keys[XK_s])
		self->dir += (t_v2f){0.0f, 1.0f};
	self->dir = ft_v2fnorm(self->dir, 140.0f * fmaxf(fminf(-dat->fire_cool[0], 1.0f), 0.5f));
	self->rot = -atan2((game->cam.pos[0] + (int)game->eng->mouse_x)
			- self->pos[0], (game->cam.pos[1] + (int)game->eng->mouse_y)
			- self->pos[1]) + M_PI_2;
	if (dat->fire_cool[0] >= 0.03125f)
	{
		ft_ent_add(game, ft_bullet_create(1, self->pos + ft_v2fr(self->rot,
					19) + ft_v2fr(self->rot + M_PI_2, 5), self->rot
				+ ft_rand(-0.5f, 0.5f) * 0.20, self->uuid));
		game->shake -= ft_v2fr(self->rot, 3);
		dat->fire_cool[0] -= 0.03125f;
	}
	self->pos += self->dir * dt;
	game->map->score += ft_v2fmag(self->dir) * dt;
}

static void	_ft_rambo_destroy(t_entity *self, t_data *game)
{
	(void)game;
	free((t_entity *)self->data);
	free((t_entity *)self);
}

t_entity	*ft_rambo_create(t_data *game, t_v2f pos)
{
	t_entity	*ent;
	t_dat_rambo	*data;

	(void)game;
	ent = ft_ent_create(1, pos, (t_v2f){0, 0}, 13.0f);
	if (ent == NULL)
		return (NULL);
	data = malloc(sizeof(t_dat_rambo));
	if (data == NULL)
		return (free(ent), NULL);
	ft_memset(data, 0, sizeof(t_dat_rambo));
	data->health = 800.0f;
	ent->data = data;
	ent->display = &_ft_rambo_display;
	ent->update = &_ft_rambo_update;
	ent->destroy = &_ft_rambo_destroy;
	ent->rot = 0.0f;
	return (ent);
}
