/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:11:28 by alde-fre          #+#    #+#             */
/*   Updated: 2023/02/02 18:35:56 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static	void	ft_game(t_engine *eng, t_data *game, double dt)
{
	ft_ent_check_activ(game);
	ft_game_update_ent(game, dt);
	ft_entity_collisions(game, dt);
	ft_game_render(game);
	ft_game_all_par(game, dt);
	ft_put_text(eng, (t_v2i){3, ft_eng_size_y(game->eng) - 9 * 2},
		"[R] Menu Principal", 2);
	if (eng->keys[XK_r])
	{
		game->state = 4;
		game->state_time = 0.0f;
	}
	if (game->state != 2)
		ft_map_unload(game);
}

int	ft_loop(t_engine *eng, t_data *data, double dt)
{
	data->time += dt;
	data->state_time += dt;
	if (data->state == 0)
		ft_menu(data, data->maps);
	else if (data->state == 1)
		ft_entry(data);
	else if (data->state == 2)
		ft_game(eng, data, dt);
	else if (data->state == 3)
	{
		ft_death(data);
		if (data->state_time > 4.0f)
		{
			data->state = 0;
			data->state_time = 0.0f;
		}
	}
	else if (data->state == 4)
		ft_exit(data, 0, 0);
	ft_put_text(data->eng, (t_v2i){ft_eng_size_x(data->eng) - 14 * 14 - 2,
		ft_eng_size_y(data->eng) - 9 * 2}, "intra:alde-fre", 2);
	// usleep(1800);
	return (1);
}

int	main(void)
{
	t_engine	*eng;
	t_data		data;

	eng = ft_eng_create(800, 600, "So Long");
	if (eng)
	{
		if (ft_init_game(eng, &data))
		{
			ft_eng_play(eng, &data, ft_loop);
			ft_maps_destroy(&data);
		}
		else
			ft_putstr_fd("Error: Failed to initialise the game.\n", 1);
		ft_destroy_game(&data);
		ft_eng_destroy(eng);
	}
	return (0);
}
