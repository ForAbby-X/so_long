/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:11:28 by alde-fre          #+#    #+#             */
/*   Updated: 2022/11/28 18:45:19 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "game.h"

int	ft_start(t_engine *eng, t_data *data)
{
	ft_putstr_fd("start!\n", 1);
	return (ft_init_game(eng, data));
}

int	ft_loop(t_engine *eng, t_data *data, double dt)
{	
	(void)eng;
	(void)dt;
	ft_ent_check_activ(data);
	ft_game_upd_ent(data, dt);
	ft_game_render(data);
	ft_game_all_par(data, dt);
	ft_entity_collisions(data);
	ft_cast_ray(data, data->eplay->pos,
		(t_v2f){data->cam.pos.x + eng->mouse_x,
		data->cam.pos.y + eng->mouse_y});
	return (1);
}

int	main(void)
{
	t_engine	*eng;
	t_data		data;

	eng = ft_eng_create(800, 600, "SO GOLF ! (pose pas de questions pour le tank(ni pour les segfault))");
	if (eng)
	{
		if (ft_start(eng, &data))
			ft_eng_play(eng, &data, ft_loop);
		ft_destroy_game(&data);
		ft_eng_destroy(eng);
	}
	return (0);
}
