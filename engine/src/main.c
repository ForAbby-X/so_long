/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:11:28 by alde-fre          #+#    #+#             */
/*   Updated: 2022/11/23 17:50:57 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "game.h"

int	ft_start(t_engine *eng, t_data *data)
{
	printf("start!\n");
	ft_init_game(eng, data);
	return (1);
}

int	ft_loop(t_engine *eng, t_data *data, double dt)
{	
	(void)eng;
	(void)dt;
	ft_game_upd_ent(data, dt);
	ft_game_render(data);
	ft_game_all_par(data, dt);
	//ft_put_sprite(eng, data->spr[0], (t_v2i){ 0, 0 });
	//ft_clear(eng, ft_color(0, 255, 0, 127));
	return (1);
}

int	main(void)
{
	t_engine	*eng;
	t_data		data;

	eng = ft_eng_create(800, 600, "SO GOLF ! (pose pas de questions pour le tank(ni pour les segfault))");
	if (eng)
	{
		ft_start(eng, &data);
		ft_eng_play(eng, &data, ft_loop);
		ft_destroy_game(&data);
		ft_eng_destroy(eng);
	}
	return (0);
}
