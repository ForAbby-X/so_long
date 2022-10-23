#include "engine.h"

struct s_data
{
	t_sprite	*spr[16];
	t_v2f		pos;
	float		base_rot;
	float		top_rot;
};

int	ft_start(t_engine *eng, t_data *data)
{
	(void)eng;
	printf("start!\n");
	data->spr[0] = ft_sprite_p(eng, "assets/background.xpm");
	data->spr[1] = ft_sprite_p(eng, "assets/tank_base.xpm");
	data->spr[2] = ft_sprite_p(eng, "assets/tank_top.xpm");
	data->pos = ft_v2f(200, 200);
	data->base_rot = 0.0f;
	data->top_rot = 0.0f;
	return (1);
}

int	ft_loop(t_engine *eng, t_data *data, double et)
{
	//printf("ROT:%f\n", data->base_rot);
	if (eng->keys[XK_a])
		data->base_rot += M_PI * 4 * et;
	if (eng->keys[XK_d])
		data->base_rot -= M_PI * 4 * et;
	if (eng->keys[XK_w])
		data->pos = ft_v2fadd(data->pos, ft_v2fr(data->base_rot, 100 * et));
	if (eng->keys[XK_s])
		data->pos = ft_v2fsub(data->pos, ft_v2fr(data->base_rot, 100 * et));
	
	data->top_rot = atan2(eng->mouse_x - data->pos.x, eng->mouse_y - data->pos.y) - M_PI_2;
	
	ft_clear(eng, ft_color_d(0xFF8F8F8F));
	ft_put_sprite(eng, data->spr[0], ft_v2i(0, 0));
	//ft_v2i(eng->mouse_x, eng->mouse_y)
	ft_put_sprite_r(eng, data->spr[1], ft_v2i(data->pos.x, data->pos.y), ft_v2i(33, 27), data->base_rot);
	ft_put_sprite_r(eng, data->spr[2], ft_v2i(data->pos.x, data->pos.y), ft_v2i(17, 15), data->top_rot);
	return (1);
}

int	ft_end(t_engine *eng, t_data *data)
{	
	(void)data;
	ft_destroy_sprite(eng, data->spr[0]);
	ft_destroy_sprite(eng, data->spr[1]);
	ft_destroy_sprite(eng, data->spr[2]);
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
		ft_start(eng, &data);
		ft_eng_play(eng, &data, ft_loop);
		ft_end(eng, &data);
	}
	return (0);
}
