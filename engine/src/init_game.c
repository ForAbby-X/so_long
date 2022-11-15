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
	data->spr[4] = ft_sprite_p(eng, "assets/walls/wall_1.xpm");
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
	data->spr[15] = ft_sprite_p(eng, "assets/bullets/shell_0.xpm");
	data->spr[16] = ft_sprite_p(eng, "assets/bullets/shell_1.xpm");
	data->spr[17] = ft_sprite_p(eng, "assets/bullets/shell_2.xpm");
	data->spr[18] = ft_sprite_p(eng, "assets/ui/weapon.xpm");
	return (1);
}

static void	ft_init_map(t_data *data, t_v2i size)
{
	int		i;

	data->map.data = malloc(size.x * size.y * sizeof(t_cell));
	data->map.size = size;
	data->map.entities = ft_vector_create(1024);
	ft_vector_add(data->map.entities, ft_tank_create(data, ft_v2f(0, 0)));
	i = 0;
	while (i < size.x * size.y)
	{
			if ((rand() & 3	) == 0)
				data->map.data[i] = 1;
			else
			{
				data->map.data[i] = 0;
				if ((rand() & 31) == 0)
					ft_vector_add(data->map.entities,
						ft_ennemy_create(data, 
						ft_v2fr((i % size.x) * 32, (i / size.x) * 32), 0.0f));
			}
		i++;
	}
}

int	ft_init_game(t_engine *eng, t_data	*data)
{
	data->eng = eng;
	ft_init_textures(eng, data);
    ft_init_map(data, ft_v2i(64, 64));
	data->cam = (t_camera){{0, 0}, {eng->win_x, eng->win_y}};
	return (1);
}
