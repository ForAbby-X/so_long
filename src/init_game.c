/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 14:08:48 by alde-fre          #+#    #+#             */
/*   Updated: 2023/02/03 15:12:27 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

char	ft_get_map(t_map *map, t_v2i pos)
{
	if (pos[0] < 0 || pos[0] >= map->size[0] || pos[1] < 0
		|| pos[1] >= map->size[1])
		return ('1');
	return (map->data[pos[0] + pos[1] * map->size[0]]);
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
	while (i < SPRITES_NBR)
	{
		str = get_next_line(fd);
		if (str == NULL)
			return (get_next_line(-1),
				ft_putstr_fd("Error: get_next_line fail.\n", 2),
				0);
		*ft_strchr(str, '\n') = '\0';
		data->spr[i] = ft_sprite_p(eng, str);
		if (data->spr[i] == NULL)
			return (get_next_line(-1),
				ft_putstr_fd("Error: Couldnt find image:\"", 2),
				ft_putstr_fd(str, 2), ft_putstr_fd("\"\n", 2), free(str), 0);
		free(str);
		i++;
	}
	return (get_next_line(-1), close(fd), 1);
}

static int	ft_init_map(t_data *game)
{
	size_t	i;
	t_map	*map[3];

	game->maps = ft_pars_folder(game);
	if (game->maps == NULL)
		return (ft_putstr_fd("Error: Failed to allocate maps space.\n", 2), 0);
	if (ft_vector_size(game->maps) == 0)
		return (ft_putstr_fd("Error: No map could load.\n", 2),
			ft_vector_destroy(game->maps), game->maps = NULL, 0);
	i = 0;
	while (i < ft_vector_size(game->maps) - 1)
	{
		map[0] = ft_vector_get(game->maps, i);
		map[1] = ft_vector_get(game->maps, i + 1);
		if (ft_strncmp(map[0]->name, map[1]->name, 999) > 0)
		{
			ft_vector_swap(game->maps, i, i + 1);
			i = 0;
		}
		else
			i++;
	}
	return (1);
}

int	ft_init_game(t_engine *eng, t_data	*data)
{
	ft_memset(data, 0, sizeof(t_data));
	data->eng = eng;
	if (!ft_init_textures(eng, data))
		return (ft_putstr_fd("Error: Failed to initialise the images.\n", 2),
			0);
	if (!ft_init_map(data))
		return (0);
	data->shake = 0;
	data->cam = (t_camera){{0, 0}, {eng->win_x, eng->win_y}};
	data->state = 0;
	return (1);
}

void	ft_destroy_game(t_data *game)
{
	t_length	i;

	i = -1;
	while (game->spr[++i] && i < SPRITES_NBR)
		ft_destroy_sprite(game->eng, game->spr[i]);
}
