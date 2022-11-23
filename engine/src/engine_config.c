/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_config.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 11:00:43 by alde-fre          #+#    #+#             */
/*   Updated: 2022/11/23 15:02:28 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

size_t	ft_eng_size_x(t_engine *eng)
{
	return (eng->sel_spr->size.x);
}

size_t	ft_eng_size_y(t_engine *eng)
{
	return (eng->sel_spr->size.y);
}

void	ft_eng_sel_spr(t_engine *eng, t_sprite	*spr)
{
	if (spr == NULL)
		eng->sel_spr = eng->screen;
	else
		eng->sel_spr = spr;
}
