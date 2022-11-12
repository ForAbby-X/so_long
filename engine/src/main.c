#include "engine.h"
#include "game.h"

int	ft_start(t_engine *eng, t_data *data)
{
	printf("start!\n");
	ft_init_game(eng, data);
	return (1);
}

int	ft_loop(t_engine *eng, t_data *data, double dt)
{
	/*
	if (eng->mouse[1])
	{
		t_v2f *tempo = malloc(sizeof(t_v2f) * 3);
		tempo[0] = ft_v2fadd(data->pos, ft_v2fnorm(ft_v2f((data->cam.pos.x + (int)eng->mouse_x) - data->pos.x, (data->cam.pos.y + (int)eng->mouse_y) - data->pos.y), 55));
		tempo[1] = ft_v2fnorm(ft_v2f((data->cam.pos.x + (int)eng->mouse_x) - data->pos.x, (data->cam.pos.y + (int)eng->mouse_y) - data->pos.y), 1000);
		tempo[2].x = -atan2((data->cam.pos.x + (int)eng->mouse_x) - data->pos.x, (data->cam.pos.y + (int)eng->mouse_y) - data->pos.y) + M_PI_2;

		ft_vector_add(data->map.bullets, tempo);
	}
	if (eng->mouse[3])
	{
		t_v2f *tempo = malloc(sizeof(t_v2f) * 3);
		tempo[0] = ft_v2fadd(data->pos, ft_v2fnorm(ft_v2f((data->cam.pos.x + (int)eng->mouse_x) - data->pos.x, (data->cam.pos.y + (int)eng->mouse_y) - data->pos.y), 55));
		tempo[1] = ft_v2fnorm(ft_v2f((data->cam.pos.x + (int)eng->mouse_x) - data->pos.x, (data->cam.pos.y + (int)eng->mouse_y) - data->pos.y),400);
		tempo[2].x = -atan2((data->cam.pos.x + (int)eng->mouse_x) - data->pos.x, (data->cam.pos.y + (int)eng->mouse_y) - data->pos.y) + M_PI_2;

		ft_vector_add(data->map.bullets, tempo);
	}
	*/
	
	(void)dt;
	ft_clear(eng, ft_color_d(0xFF8F8F8F));
	ft_game_upd_ent(data, dt);
	ft_game_render(data);

	return (1);
}

int	ft_end(t_engine *eng, t_data *data)
{
	(void)eng;
	(void)data;
	ft_eng_destroy(eng);
	printf("end!\n");
	return (1);
}

int	main(void)
{
	t_engine	*eng;
	t_data		data;

	eng = ft_eng_create(800, 600, "SO GOLF ! (pose pas de questions pour le tank)");
	if (eng)
	{
		ft_start(eng, &data);
		ft_eng_play(eng, &data, ft_loop);
		ft_end(eng, &data);
	}
	return (0);
}
