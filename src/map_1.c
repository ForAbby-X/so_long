#include "map.h"

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
	map->entities = ft_vector_create();
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
	map->walls[16] = ft_sprite_p(eng, "assets/dirt.xpm");
	map->walls[17] = ft_sprite_p(eng, "assets/mob.xpm");
}

void	ft_destroy_map(t_map *map)
{
	free(map->data);
}

void	ft_put_map(t_engine *eng, t_camera cam, t_map *map)
{
	t_v2i	pos;
	t_v2i	rpos;
	t_v2i	wpos;

	pos.y = -1;
	while (pos.y <= cam.dim.y / 32 + 1)
	{
		pos.x = -1;
		while (pos.x <= cam.dim.x / 32 + 1)
		{
			rpos.x = (pos.x - (cam.pos.x / 32.0 - cam.pos.x / 32)) * 32;
			rpos.y = (pos.y - (cam.pos.y / 32.0 - cam.pos.y / 32)) * 32;
			wpos = ft_v2iadd(pos, ft_v2idiv(cam.pos, 32));
			ft_put_sprite(eng, map->walls[16], rpos);
			if (ft_get_map(map, wpos))
				ft_put_sprite(eng, map->walls[ft_get_map(map, wpos) - 1], rpos);
			pos.x++;
		}
		pos.y++;
	}
	int	i = 0;
	while (i < 100)
	{
		t_v2i pos = (*(t_v2i *)ft_vector_get(map->entities, i));
		pos = ft_v2isub(pos, cam.pos);
		pos = ft_v2isub(pos, ft_v2i(16, 16));
		ft_put_sprite(eng, map->walls[17], pos);
		i++;
	}
}
