/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 13:43:43 by alde-fre          #+#    #+#             */
/*   Updated: 2023/01/27 16:59:42 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	ft_check_col(t_color a, t_color b, int diff)
{
	int	col[3];

	col[0] = ((int)(a.d >> 16) & 0xFF) - ((int)(b.d >> 16) & 0xFF);
	col[1] = ((int)(a.d >> 8) & 0xFF) - ((int)(b.d >> 8) & 0xFF);
	col[2] = ((int)(a.d) & 0xFF) - ((b.d) & 0xFF);
	if ((col[0] >= diff || col[0] < -diff)
		|| (col[1] >= diff || col[1] < -diff)
		|| (col[2] >= diff || col[2] < -diff))
		return (0);
	return (1);
}

int	ft_check_col_zone(t_sprite *spr, t_v2i pos, t_color b, int diff)
{
	t_v2i	xy;

	xy[1] = pos[1] - 5;
	while (xy[1] < pos[1] + 5)
	{
		xy[0] = pos[0] - 5;
		while (xy[0] < pos[0] + 5)
		{
			if (ft_check_col(ft_get_color(spr, xy), b, diff))
				return (1);
			xy[0]++;
		}
		xy[1]++;
	}
	return (0);
}