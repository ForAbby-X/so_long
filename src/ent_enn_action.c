/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ent_enn_action.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 14:13:06 by alde-fre          #+#    #+#             */
/*   Updated: 2023/02/02 14:18:23 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	ft_damage_enn(t_data *game, t_entity *ent, float damage, float rot)
{
	t_dat_enn_base	*dat;

	dat = ent->data;
	dat->health -= damage;
	ft_emmit_blood(game, 10, ent->pos, rot);
	ft_eng_sel_spr(game->eng, game->map->background);
	ft_put_sprite_r(game->eng, game->spr[23],
		(t_rect){{ent->pos[0], ent->pos[1]}, {11, 13}}, rot
		+ ft_rand(-0.2f, 0.2f));
	ft_eng_sel_spr(game->eng, 0);
}
