#include "engine.h"
#include "map.h"

struct s_data
{
	t_sprite	*spr[16];
	t_map		map;
	t_v2f		ine;
	t_v2f		pos;
	t_v2f		dir;
	float		acc;
	float		vel;
	float		base_rot;
	float		top_rot;
	t_camera	cam;
};

int	ft_start(t_engine *eng, t_data *data)
{
	printf("start!\n");
	data->spr[0] = ft_sprite_p(eng, "assets/background.xpm");
	data->spr[1] = ft_sprite_p(eng, "assets/tank_base.xpm");
	data->spr[2] = ft_sprite_p(eng, "assets/tank_top.xpm");
	ft_init_map(eng, &data->map, ft_v2i(64, 64));
	data->pos = ft_v2f(200, 200);
	data->ine = ft_v2f(0, 0);
	data->dir = ft_v2f(0, 0);
	data->acc = 0.0f;
	data->vel = 0.0f;
	data->base_rot = 0.0f;
	data->top_rot = 0.0f;
	data->cam = (t_camera){{0, 0}, {eng->win_x, eng->win_y}};
	return (1);
}

int	ft_loop(t_engine *eng, t_data *data, double dt)
{
	//printf("ROT:%f\n", data->base_rot);
	if (eng->keys[XK_a])
		data->base_rot -= M_PI * dt * (1.0f - data->vel / 150.0f);
	if (eng->keys[XK_d])
		data->base_rot += M_PI * dt * (1.0f - data->vel / 150.0f);
		
	data->dir = ft_v2fr(data->base_rot, 1.0f);
	if (eng->keys[XK_w])
	{
		data->ine = ft_v2fmul(data->dir, 1);
		data->vel += 8.0f;
	}
	if (eng->keys[XK_s])
	{
		data->ine = ft_v2fmul(data->dir, -1);
		data->vel += 3.0f;
	}
	
	data->acc = sinf(fabsf(ft_v2fdot(data->dir, data->ine)) * M_PI_2);
	data->vel = data->vel * 0.96f * (data->acc * data->acc);
	if (data->vel < -70.0f)
		data->vel = -70.0f;
	if (data->vel > 100.0f)
		data->vel = 100.0f;
	data->pos = ft_v2fadd(data->pos, ft_v2fmul(data->ine, data->vel * dt));
	
	/* display everything */
	data->cam.pos = ft_v2i(data->pos.x - data->cam.dim.x / 2, data->pos.y - data->cam.dim.y / 2);
	data->top_rot = -atan2((data->cam.pos.x + (int)eng->mouse_x) - data->pos.x, (data->cam.pos.y + (int)eng->mouse_y) - data->pos.y) + M_PI_2;

	ft_clear(eng, ft_color_d(0xFF8F8F8F));
	ft_put_map(eng, data->cam, &data->map);
	
	ft_put_sprite_r(eng, data->spr[1], ft_v2i(data->pos.x - data->cam.pos.x, data->pos.y - data->cam.pos.y), ft_v2i(33, 27), data->base_rot);
	ft_put_sprite_r(eng, data->spr[2], ft_v2i(data->pos.x - data->cam.pos.x, data->pos.y - data->cam.pos.y), ft_v2i(17, 15), data->top_rot);
	
	//ft_circle(eng, ft_v2i(data->pos.x, data->pos.y), 30, ft_color(255, 255, 0, 0));
	//ft_circle(eng, ft_v2iadd(ft_v2i(data->pos.x, data->pos.y), ft_v2i(data->vel, 0)), 3, ft_color_d(0xFFFF00FF));
	ft_circle(eng, ft_v2i(data->cam.pos.x - data->pos.x, data->cam.pos.x - data->pos.y), 30, ft_color_d(0xFFFFFFFF));
	
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

	eng = ft_eng_create(600, 400, "SO GOLF ! (pose pas de questions pour le tank)");
	if (eng)
	{
		ft_start(eng, &data);
		ft_eng_play(eng, &data, ft_loop);
		ft_end(eng, &data);
	}
	return (0);
}
