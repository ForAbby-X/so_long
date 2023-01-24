/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 10:55:22 by alde-fre          #+#    #+#             */
/*   Updated: 2022/12/10 15:59:03 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	ft_eng_destroy(t_engine *eng)
{
	mlx_loop_end(eng->mlx);
	ft_destroy_sprite(eng, eng->screen);
	ft_destroy_sprite(eng, eng->ascii_spr);
	mlx_destroy_window(eng->mlx, eng->win);
	mlx_destroy_display(eng->mlx);
	free(eng->mlx);
	free(eng);
	ft_putstr_fd("Destroying engine...\n", 1);
}

int	ft_eng_play(t_engine *eng, t_data *data,
		int (*on_repeat)(t_engine *eng, t_data *data, double elapsed_time))
{
	ft_putstr_fd("Starting engine...\n", 1);
	if (on_repeat)
	{
		eng->data = data;
		eng->on_repeat = on_repeat;
		clock_gettime(CLOCK_MONOTONIC, &eng->time_e);
		mlx_loop(eng->mlx);
	}
	return (1);
}
