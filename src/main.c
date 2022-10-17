#include "engine.h"

typedef struct
{
	int		x;
	int		y;
	int		r;
	t_color	color;
}	t_circle;

struct s_data
{
	t_circle	c_a;
	t_circle	c_b;
	t_sprite	*spr;
	t_sprite	*spr2;
};

int	ft_start(t_engine *eng, t_data *data)
{
	(void)eng;
	printf("start!\n");
	data->spr = ft_sprite_p(eng, "spaceship.xpm");
	data->spr2 = ft_sprite_p(eng, "background.xpm");
	return (1);
}

int	ft_loop(t_engine *eng, t_data *data, float et)
{
	(void)et;

	ft_clear(eng, ft_color_d(0xFF8F8F8F));
	if (eng->mouse[1])
	{
		data->c_a.x = eng->mouse_x;
		data->c_a.y = eng->mouse_y;
	}
	if (eng->mouse[3])
	{
		data->c_b.x = eng->mouse_x;
		data->c_b.y = eng->mouse_y;
	}
	ft_put_sprite(eng, data->spr2, ft_v2i(0, 0));
	ft_circle(eng, ft_v2i(data->c_a.x, data->c_a.y), data->c_a.r, data->c_a.color);
	ft_circle(eng, ft_v2i(data->c_b.x, data->c_b.y), data->c_b.r, data->c_b.color);
	ft_put_sprite_s(eng, data->spr, ft_v2i(eng->mouse_x, eng->mouse_y), 3);
	return (1);
}

int	ft_end(t_engine *eng, t_data *data)
{	
	(void)data;
	ft_destroy_sprite(data->spr);
	ft_destroy_sprite(data->spr2);
	ft_eng_destroy(eng);
	printf("end!\n");
	return (1);
}

int	main(void)
{
	t_engine	*eng;
	t_data		data;

	eng = ft_eng_create(400, 400, "SO GOLF !");
	if (eng)
	{
		data = (t_data){
			{80, 100, 30, ft_color_d(0xFF0000FF)},
			{100, 40, 40, ft_color_d(0xFF00FFFF)},
			0, 0};
		ft_start(eng, &data);
		ft_eng_play(eng, &data, ft_loop);
		ft_end(eng, &data);
	}
	return (0);
}
