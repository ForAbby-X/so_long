/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 14:08:48 by alde-fre          #+#    #+#             */
/*   Updated: 2022/11/23 17:45:27 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	ft_get_map(t_map *map, t_v2i pos)
{
	if (pos.x < 0 || pos.x >= map->size.x || pos.y < 0 || pos.y >= map->size.y)
		return (0);
	return (map->data[pos.x + pos.y * map->size.x]);
}

static int	ft_init_textures(t_engine *eng, t_data	*data)
{
	data->spr[0] = ft_sprite_p(eng, "assets/tank/tank_base.xpm");
	data->spr[1] = ft_sprite_p(eng, "assets/tank/tank_top.xpm");
	data->spr[2] = ft_sprite_p(eng, "assets/ground/dirt.xpm");
	data->spr[3] = ft_sprite_p(eng, "assets/walls/wall_0.xpm");
	data->spr[4] = ft_sprite_p(eng, "assets/walls/h_wall_0.xpm");
	data->spr[5] = ft_sprite_p(eng, "assets/bullets/bullets_small.xpm");
	data->spr[6] = ft_sprite_p(eng, "assets/bullets/bullets_big.xpm");
	data->spr[7] = ft_sprite_p(eng, "assets/ennemies/ennemy_walk_0.xpm");
	data->spr[8] = ft_sprite_p(eng, "assets/ennemies/ennemy_walk_1.xpm");
	data->spr[9] = ft_sprite_p(eng, "assets/ennemies/ennemy_shoot_0.xpm");
	data->spr[10] = ft_sprite_p(eng, "assets/ennemies/ennemy_shoot_1.xpm");
	data->spr[11] = ft_sprite_p(eng, "assets/ennemies/ennemy_run_0.xpm");
	data->spr[12] = ft_sprite_p(eng, "assets/ennemies/ennemy_run_1.xpm");
	data->spr[13] = ft_sprite_p(eng, "assets/ennemies/ennemy_wait_0.xpm");
	data->spr[14] = ft_sprite_p(eng, "assets/ennemies/ennemy_wait_1.xpm");
	data->spr[15] = ft_sprite_p(eng, "assets/stain/ennemy_dead.xpm");
	data->spr[16] = ft_sprite_p(eng, "assets/bullets/shell_0.xpm");
	data->spr[17] = ft_sprite_p(eng, "assets/bullets/shell_1.xpm");
	data->spr[18] = ft_sprite_p(eng, "assets/bullets/shell_2.xpm");
	data->spr[19] = ft_sprite_p(eng, "assets/ui/weapon.xpm");
	data->spr[20] = ft_sprite_p(eng, "assets/particles/spark.xpm");
	data->spr[21] = ft_sprite_p(eng, "assets/particles/blood.xpm");
	data->spr[22] = ft_sprite_p(eng, "assets/particles/smoke_small.xpm");
	data->spr[23] = ft_sprite_p(eng, "assets/stain/blood_splash_small.xpm");
	data->spr[24] = ft_sprite_p(eng, "assets/stain/blood_splash_big.xpm");
	return (1);
}

static void	ft_init_map(t_data *data, t_v2i size)
{
	int		i;

	data->map.data = malloc(size.x * size.y * sizeof(t_cell));
	data->map.size = size;
	data->map.entities = ft_vector_create(1024);
	data->map.particles = ft_vector_create(1024);
	ft_vector_add(data->map.entities, ft_tank_create(data, ft_v2f(200, 200)));
	data->player = ((t_entity *)ft_vector_get(data->map.entities, 0))->data;
	i = 0;
	while (i < size.x * size.y)
	{
		if ((rand() & 7) == 0)
			data->map.data[i] = 1;
		else
		{
			data->map.data[i] = 0;
			if ((rand() & 31) == 0)
			{
				ft_vector_add(data->map.entities,
					ft_ennemy_create(data,
						ft_v2f((i % size.x) * 32, (i / size.x) * 32), 0.0f));
			}
		}
		i++;
	}
}

int	ft_init_game(t_engine *eng, t_data	*data)
{
	data->eng = eng;
	ft_init_textures(eng, data);
	ft_init_map(data, ft_v2i(128, 128));
	data->map.background = ft_sprite(eng, data->map.size.x * 32,
			data->map.size.y * 32);
	ft_eng_sel_spr(eng, data->map.background);
	ft_clear(eng, ft_color_d(0xFF000000));
	ft_eng_sel_spr(eng, 0);
	data->shake = 0;
	data->cam = (t_camera){{0, 0}, {eng->win_x, eng->win_y}};
	return (1);
}

void	ft_destroy_game(t_data *game)
{
	t_length	i;

	i = 0;
	while (i < 25)
		ft_destroy_sprite(game->eng, game->spr[i++]);
	free(game->map.data);
	i = 0;
	while (i < ft_vector_size(game->map.entities))
	{
		free(((t_entity *)ft_vector_get(game->map.entities, i))->data);
		free(((t_entity *)ft_vector_get(game->map.entities, i)));
		i++;
	}
	i = 0;
	while (i < ft_vector_size(game->map.particles))
		free(((t_particle *)ft_vector_get(game->map.particles, i++)));
	ft_vector_destroy(game->map.entities);
	ft_vector_destroy(game->map.particles);
	ft_destroy_sprite(game->eng, game->map.background);
}
