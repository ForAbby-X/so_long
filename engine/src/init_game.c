#include "game.h"

int	ft_get_map(t_map *map, t_v2i pos)
{
	if (pos.x < 0 || pos.x >= map->size.x || pos.y < 0 || pos.y >= map->size.y)
		return (0);
	return (map->data[pos.x + pos.y * map->size.x]);
}

static int	ft_init_textures(t_engine *eng, t_data	*data)
{
	data->spr[0] = ft_sprite_p(eng, "assets/tank_base.xpm");
	data->spr[1] = ft_sprite_p(eng, "assets/tank_top.xpm");
    data->spr[2] = ft_sprite_p(eng, "assets/dirt.xpm");
	data->spr[3] = ft_sprite_p(eng, "assets/walls/wall_0.xpm");
    data->spr[4] = ft_sprite_p(eng, "assets/ennemy.xpm");
    data->spr[5] = ft_sprite_p(eng, "assets/bullets.xpm");
	return (1);
}

static void	ft_init_map(t_map *map, t_v2i size)
{
	int		i;

	map->data = malloc(size.x * size.y * sizeof(t_cell));
	map->size = size;
	map->entities = ft_vector_create(1);
	i = 0;
	while (i < size.x * size.y)
	{
			if ((rand() & 3	) == 0)
				map->data[i] = 1;
			else
				map->data[i] = 0;
		i++;
	}
}

int	ft_init_game(t_engine *eng, t_data	*data)
{
	data->eng = eng;
	ft_init_textures(eng, data);
    ft_init_map(&data->map, ft_v2i(64, 64));
	data->cam = (t_camera){{0, 0}, {eng->win_x, eng->win_y}};
	data->map.entities = ft_vector_create(1024);
	ft_vector_add(data->map.entities, ft_tank_create(data, ft_v2f(64, 64)));
	ft_vector_add(data->map.entities, ft_ennemy_create(data, ft_v2f(64, 64), 0.0f));
	ft_vector_add(data->map.entities, ft_ennemy_create(data, ft_v2f(64, 64), 1.0f));
	ft_vector_add(data->map.entities, ft_ennemy_create(data, ft_v2f(64, 64), 1.5f));
	ft_vector_add(data->map.entities, ft_ennemy_create(data, ft_v2f(64, 64), 2.0f));
	ft_vector_add(data->map.entities, ft_ennemy_create(data, ft_v2f(64, 64), 2.5f));
	ft_vector_add(data->map.entities, ft_ennemy_create(data, ft_v2f(64, 64), 3.0f));
	return (1);
}
