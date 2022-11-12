#include "game.h"

int	ft_get_map(t_map *map, t_v2i pos)
{
	if (pos.x < 0 || pos.y < 0 || pos.x >= map->size.x || pos.y >= map->size.y)
		return (0);
	return (map->data[pos.x + pos.y * map->size.x]);
}

void	ft_init_map(t_engine *eng, t_map *map, t_v2i size)
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
	i = 0;
	while (i < 1000)
	{
		t_v2i	*o = malloc(sizeof(t_v2i));
		o->x = rand() % eng->win_x * 10;
		o->y = rand() % eng->win_y * 10;
		ft_vector_add(map->entities, o);
		i++;
	}
	map->bullets = ft_vector_create(1024);
}

void	ft_destroy_map(t_map *map)
{
	free(map->data);
}

void	ft_put_map(t_engine *eng, t_camera cam, t_map *map)
{
	unsigned int	i = 0;
	while (i < ft_vector_size(map->entities))
	{
		//t_entity *ent = (t_entity *)ft_vector_get(map->entities, i);
		//ent->display((t_data *)map - sizeof(t_sprite *) - sizeof(t_engine	*), ent);
		i++;
	}
	i = 0;
	while (i < ft_vector_size(map->bullets))
	{
		t_v2f pos = (*(t_v2f *)ft_vector_get(map->bullets, i));
		float rot = ((t_v2f *)ft_vector_get(map->bullets, i))[2].x;
		//t_v2i dir = ((t_v2f *)ft_vector_get(map->bullets, i))[1];
		ft_put_sprite_r(eng, map->walls[18], ft_v2isub(ft_v2i(pos.x, pos.y - 12), cam.pos), ft_v2i(28, 4), rot);
		//ft_circle(eng, ft_v2isub(ft_v2i(pos.x, pos.y - 12), cam.pos), 10, ft_color(255, 255, 0, 0));
		i++;
	}
}
