/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coin.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 18:06:42 by alde-fre          #+#    #+#             */
/*   Updated: 2024/06/28 18:07:53 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	_ft_coin_display(t_entity *self, t_data *game)
{
	t_dat_coin	*data;

	data = self->data;
	ft_put_sprite_r(game->eng, game->spr[31], (t_rect){{self->pos[0]
		- game->cam.pos[0], self->pos[1] - game->cam.pos[1]},
		(t_v2i){16, 16}}, self->rot);
	ft_put_sprite(game->eng, game->spr[32], (t_v2i){self->pos[0] - 6
		- game->cam.pos[0], self->pos[1] - (26 + sinf(data->time * 4) * 8)
		- game->cam.pos[1]});
}

static void	_ft_coin_update(t_entity *self, t_data *game, float dt)
{
	t_dat_coin	*data;

	data = self->data;
	data->time += dt;
	if (!game->is_finished && ft_v2fmag(game->eplay->pos - self->pos)
		< game->eplay->radius + self->radius + 1)
	{
		ft_eng_sel_spr(game->eng, game->map->background);
		ft_put_sprite_r(game->eng, game->spr[36],
			(t_rect){{self->pos[0], self->pos[1]}, {16, 16}}, self->rot);
		ft_eng_sel_spr(game->eng, NULL);
		ft_emmit_wood(game, self->pos);
		if (game->eplay->type == 0)
		{
			ft_emmit_gear(game, game->eplay->pos, 3);
			((t_dat_tank *)game->tplay)->health
				= fminf(((t_dat_tank *)game->tplay)->health + 300.0f, 2000.0f);
		}
		game->crate_nb++;
		self->alive = 0;
	}
}

static void	_ft_coin_destroy(t_entity *self, t_data *game)
{
	(void)game;
	free((t_entity *)self->data);
}

t_entity	ft_coin_create(t_v2f pos)
{
	t_entity	ent;
	t_dat_coin	*data;

	ent = ft_ent_create(8, pos, (t_v2f){0, 0}, 13);
	data = malloc(sizeof(t_dat_coin));
	if (data == NULL)
		return ((t_entity){0});
	data->time = 0.0f;
	ent.data = data;
	ent.display = &_ft_coin_display;
	ent.update = &_ft_coin_update;
	ent.destroy = &_ft_coin_destroy;
	ent.rot = ft_rand(-M_PI, M_PI);
	return (ent);
}
