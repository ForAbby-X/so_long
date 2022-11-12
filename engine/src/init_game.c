#include "game.h"

static int	ft_init_textures(t_engine *eng, t_data	*data)
{
	data->spr[0] = ft_sprite_p(eng, "assets/tank_base.xpm");
	data->spr[1] = ft_sprite_p(eng, "assets/tank_top.xpm");
    data->spr[2] = ft_sprite_p(eng, "assets/dirt.xpm");
	data->spr[3] = ft_sprite_p(eng, "assets/walls/wall_0.xpm");
    data->spr[4] = ft_sprite_p(eng, "assets/mob.xpm");
    data->spr[5] = ft_sprite_p(eng, "assets/bullets.xpm");
	return (1);
}

int	ft_init_game(t_engine *eng, t_data	*data)
{
	data->eng = eng;
	ft_init_textures(eng, data);
    ft_init_map(eng, &data->map, ft_v2i(64, 64));
	data->cam = (t_camera){{0, 0}, {eng->win_x, eng->win_y}};
	data->map.entities = ft_vector_create(1024);
	ft_vector_add(data->map.entities, ft_tank_create(data, ft_v2f(64, 64)));
	return (1);
}
