/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tank.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:27:25 by alde-fre          #+#    #+#             */
/*   Updated: 2023/02/15 16:01:29 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	_ft_tank_display(t_entity *self, t_data *game)
{
	t_dat_tank	*dat;

	dat = self->data;
	ft_put_sprite_r(game->eng, dat->spr, (t_rect){{self->pos[0]
		- game->cam.pos[0], self->pos[1] - game->cam.pos[1]},
	{33, 27}}, self->rot);
	ft_put_sprite_r(game->eng, game->spr[1], (t_rect){{self->pos[0]
		- game->cam.pos[0], self->pos[1] - game->cam.pos[1]},
	{17, 15}}, dat->top_rot);
	if (dat->timer >= 0.0625f)
	{
		ft_emmit_smoke_pipe(game, 2, (t_v2f){self->pos[0], self->pos[1]}
			+ ft_v2fr(self->rot, -25));
		ft_eng_sel_spr(game->eng, game->map->background);
		ft_paint_trail(game, (t_v2i){self->pos[0], self->pos[1]}
			- ft_v2irot((t_v2i){0, 20}, self->rot), self->rot, 2.0f
			- dat->bloody[0]);
		ft_paint_trail(game, (t_v2i){self->pos[0], self->pos[1]}
			+ ft_v2irot((t_v2i){0, 20}, self->rot), self->rot, 2.0f
			- dat->bloody[1]);
		ft_eng_sel_spr(game->eng, NULL);
		dat->timer -= 0.0625f;
	}
}

static void	_ft_tank_destroy(t_entity *self, t_data *game)
{
	ft_destroy_sprite(game->eng, ((t_dat_tank *)self->data)->spr);
	free((t_entity *)self->data);
	free((t_entity *)self);
}

t_entity	*ft_tank_create(t_data *game, t_v2f pos)
{
	t_entity	*ent;
	t_dat_tank	*data;

	ent = ft_ent_create(0, pos, (t_v2f){0, 0}, 31.0f);
	if (ent == NULL)
		return (NULL);
	data = malloc(sizeof(t_dat_tank));
	if (data == NULL)
		return (free(ent), NULL);
	ft_memset(data, 0, sizeof(t_dat_tank));
	data->spr = ft_cpy_sprite(game->eng, game->spr[0]);
	if (data->spr == NULL)
		return (free(data), free(ent), NULL);
	ent->data = data;
	ent->display = &_ft_tank_display;
	ent->update = &ft_tank_update;
	ent->destroy = &_ft_tank_destroy;
	ent->rot = ft_rand(-M_PI, M_PI);
	ft_eng_sel_spr(game->eng, game->map->background);
	ft_put_sprite_r(game->eng, game->spr[41],
		(t_rect){{pos[0], pos[1]}, {84, 96}}, ent->rot);
	ft_eng_sel_spr(game->eng, NULL);
	return (ent);
}
