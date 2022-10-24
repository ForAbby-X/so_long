#include "map.h"

static void	ft_init_map2(t_map *map)
{
	t_v2i	pos;

	pos.y = 0;
	while (pos.y < map->size.y)
	{
		pos.x = 0;
		while (pos.x < map->size.x)
		{
			map->data[pos.x + pos.y * map->size.x].wall = ft_get_map(map, ft_v2iadd(pos, ft_v2i(1, 0))) != 0;
			map->data[pos.x + pos.y * map->size.x].wall |= (ft_get_map(map, ft_v2iadd(pos, ft_v2i(-1, 0))) != 0) << 1;
			map->data[pos.x + pos.y * map->size.x].wall |= (ft_get_map(map, ft_v2iadd(pos, ft_v2i(0, 1))) != 0) << 2;
			map->data[pos.x + pos.y * map->size.x].wall |= (ft_get_map(map, ft_v2iadd(pos, ft_v2i(0, -1))) != 0) << 3;
			
			pos.x++;
		}
		pos.y++;
	}
}

void	ft_init_map(t_engine *eng, t_map *map, t_v2i size)
{
	int		i;

	map->data = malloc(size.x * size.y * sizeof(t_cell));
	map->size = size;
	i = 0;
	while (i < size.x * size.y)
	{
			if ((rand() & 3) != 0)
				map->data[i].wall = 1;
			else
				map->data[i].wall = 0;
		i++;
	}
	ft_init_map2(map);
	map->walls[0] = ft_sprite_p(eng, "assets/walls/wall_0.xpm");
	map->walls[1] = ft_sprite_p(eng, "assets/walls/wall_1.xpm");
	map->walls[2] = ft_sprite_p(eng, "assets/walls/wall_2.xpm");
	map->walls[3] = ft_sprite_p(eng, "assets/walls/wall_3.xpm");
	map->walls[4] = ft_sprite_p(eng, "assets/walls/wall_4.xpm");
	map->walls[5] = ft_sprite_p(eng, "assets/walls/wall_5.xpm");
	map->walls[6] = ft_sprite_p(eng, "assets/walls/wall_6.xpm");
	map->walls[7] = ft_sprite_p(eng, "assets/walls/wall_7.xpm");
	map->walls[8] = ft_sprite_p(eng, "assets/walls/wall_8.xpm");
	map->walls[9] = ft_sprite_p(eng, "assets/walls/wall_9.xpm");
	map->walls[10] = ft_sprite_p(eng, "assets/walls/wall_10.xpm");
	map->walls[11] = ft_sprite_p(eng, "assets/walls/wall_11.xpm");
	map->walls[12] = ft_sprite_p(eng, "assets/walls/wall_12.xpm");
	map->walls[13] = ft_sprite_p(eng, "assets/walls/wall_13.xpm");
	map->walls[14] = ft_sprite_p(eng, "assets/walls/wall_14.xpm");
	map->walls[15] = ft_sprite_p(eng, "assets/walls/wall_15.xpm");
}

void	ft_destroy_map(t_map *map)
{
	free(map->data);
}

void	ft_put_map(t_engine *eng, t_map *map)
{
	t_v2i	pos;

	pos.y = 0;
	while (pos.y < map->size.y)
	{
		pos.x = 0;
		while (pos.x < map->size.x)
		{
			ft_put_sprite(eng, map->walls[map->data
				[pos.x + pos.y * map->size.x].wall], ft_v2imul(pos, 32));
			pos.x++;
		}
		pos.y++;
	}
}

int	ft_get_map(t_map *map, t_v2i pos)
{
	if (pos.x < 0 || pos.y < 0 || pos.x >= map->size.x || pos.y >= map->size.y)
		return (0);
	return (map->data[pos.x + pos.y * map->size.x].wall);
}
