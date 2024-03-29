/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [2]menu.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:11:46 by alde-fre          #+#    #+#             */
/*   Updated: 2023/02/17 17:09:08 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	ft_exit(t_data *game, int crates, float meter)
{
	(void)meter;
	(void)crates;
	ft_rect(game->eng, (t_v2i){14, 16}, (t_v2i){21 * 7 * 4, 9 * 4},
		(t_color){0x426270});
	ft_put_text(game->eng, (t_v2i){14, 16}, "Extraction reussite !", 4);
	ft_rect(game->eng, (t_v2i){20, 96}, (t_v2i){30 * 7 * 3, 9 * 3 * 6},
		(t_color){0x81A19C});
	if (game->state_time > 1.0f)
	{
		ft_put_text(game->eng, (t_v2i){20, 96}, "caisses collecte:", 3);
		ft_put_nbr(game->eng, (t_v2i){20 + 17 * 7 * 3, 96}, game->crate_nb, 3);
	}
	if (game->state_time > 2.5f)
	{
		ft_put_text(game->eng, (t_v2i){20, 156}, "metres parcourus:", 3);
		ft_put_nbr(game->eng, (t_v2i){20 + 17 * 7 * 3, 156}, game->score / 32,
			3);
	}
	if (game->state_time > 6.0f)
	{
		game->state = 0;
		game->state_time = 0.0f;
	}
}
