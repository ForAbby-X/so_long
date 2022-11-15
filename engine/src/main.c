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
