/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 14:08:48 by alde-fre          #+#    #+#             */
/*   Updated: 2022/11/25 11:59:42 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	ft_get_map(t_map *map, t_v2i pos)
{
	printf("[%d:%d]\n", pos.x, pos.y);
	if (pos.x < 0 || pos.x >= map->size.x || pos.y < 0 || pos.y >= map->size.y)
		return (0);
	return (map->data[pos.x + pos.y * map->size.x]);
}

static int	ft_init_textures(t_engine *eng, t_data	*data)
{
	int		i;
	int		fd;
	char	*str;

	fd = open("assets/textures_list.lst", O_RDONLY);
	if (fd < 0)
		return (0);
	i = 0;
	while (i < 26)
	{
		str = get_next_line(fd);
		if (str == NULL)
			return (get_next_line(-1), 0);
		str[ft_strlen(str) - 1] = '\0';
		data->spr[i] = ft_sprite_p(eng, str);
		free(str);
		if (data->spr[i] == NULL)
			return (get_next_line(-1), 0);
		i++;
	}
	get_next_line(-1);
	close(fd);
	return (1);
}

static int	ft_init_map(t_data *data, t_v2i size)
{
	int		i;

	data->map.data = malloc(size.x * size.y * sizeof(int));
	if (data->map.data == NULL)
		return (0);
	data->map.size = size;
	data->map.entities = ft_vector_create(1024);
	data->map.particles = ft_vector_create(1024);
	if (data->map.entities == NULL || data->map.particles == NULL)
		return (0);
	ft_ent_add(data, ft_tank_create(data, ft_v2f(200, 200)));
	data->eplay = ft_vector_get(data->map.entities, 0);
	data->dplay = data->eplay->data;
	i = -1;
	while (++i < size.x * size.y)
	{
		if ((rand() & 7) == 0)
			data->map.data[i] = 1;
		else
		{
			data->map.data[i] = 0;
			if ((rand() & 15) == 0)
			{
				ft_ent_add(data, ft_ennemy_create(
						ft_v2f((i % size.x) * 32, (i / size.x) * 32), 0.0f));
			}
		}
	}
	return (1);
}

int	ft_init_game(t_engine *eng, t_data	*data)
{
	ft_memset(data, 0, sizeof(t_data));
	data->eng = eng;
	if (!ft_init_textures(eng, data))
		return (0);
	if (!ft_init_map(data, ft_v2i(128, 128)))
		return (0);
	data->map.background = ft_sprite(eng, data->map.size.x * 32,
			data->map.size.y * 32);
	if (data->map.background == NULL)
		return (0);
	ft_eng_sel_spr(eng, data->map.background);
	ft_clear(eng, (t_color){0xFF000000});
	ft_eng_sel_spr(eng, 0);
	data->shake = 0;
	data->cam = (t_camera){{0, 0}, {eng->win_x, eng->win_y}};
	return (1);
}

void	ft_destroy_game(t_data *game)
{
	t_length	i;
	t_entity	*ent;

	i = 0;
	while (game->spr[i] && i < 26)
		ft_destroy_sprite(game->eng, game->spr[i++]);
	if (game->map.data)
		free(game->map.data);
	i = 0;
	while (game->map.entities && i < ft_vector_size(game->map.entities))
	{
		ent = (t_entity *)ft_vector_get(game->map.entities, i++);
		ent->destroy(ent, game);
	}
	i = 0;
	while (game->map.particles && i < ft_vector_size(game->map.particles))
		free(((t_particle *)ft_vector_get(game->map.particles, i++)));
	if (game->map.entities)
		ft_vector_destroy(game->map.entities);
	if (game->map.particles)
		ft_vector_destroy(game->map.particles);
	if (game->map.background)
		ft_destroy_sprite(game->eng, game->map.background);
}
