#include "engine.h"

static t_v2i	ft_get_border(t_engine *eng, t_sprite *spr, t_v2i pos, t_v2i cen, float rot)
{
	t_v2i	cor[4];
	
	t_v2i	min;
	t_v2i	max;
	
	cor[0] = ft_v2isub(pos, ft_v2irot(cen, rot)); 
	cor[1] = ft_v2iadd(pos, ft_v2irot(ft_v2i(-cen.x, spr->size.y - cen.y), rot));
	cor[2] = ft_v2iadd(pos, ft_v2irot(ft_v2i(spr->size.x - cen.x, -cen.y), rot));
	cor[3] = ft_v2iadd(pos, ft_v2irot(ft_v2isub(spr->size, cen), rot));
	
	(void)cor;
	
	printf("%f\n", rot);
	
	if (rot <= 0 && rot > -M_PI / 2)
	{
		min.x = pos.x + cosf(rot) * -cen.x + sinf(rot) * (spr->size.y - cen.y);
		min.y = pos.y - -sinf(rot) * cen.x + cosf(rot) * cen.y;
		max.x = pos.x + cosf(rot) * -cen.x + sinf(rot) * (spr->size.y - cen.y);
		max.y = pos.y + -sinf(rot) * (spr->size.x - cen.x) + cosf(rot) * (spr->size.y - cen.y);
	}	
	
	//b.x = cosf(rot) * a.x + sinf(rot) * a.y;
	//b.y = -sinf(rot) * a.x + cosf(rot) * a.y;
	
	ft_circle(eng, min, 3, ft_color(255, 000, 000, 255));
	ft_circle(eng, max, 3, ft_color(255, 255, 000, 000));
	return (ft_v2i(0, 0));
}

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
	t_sprite	*spr[16];
	float		rot;
};

int	ft_start(t_engine *eng, t_data *data)
{
	(void)eng;
	printf("start!\n");
	data->spr[0] = ft_sprite_p(eng, "assets/background.xpm");
	data->spr[1] = ft_sprite_p(eng, "assets/tank_base.xpm");
	data->spr[2] = ft_sprite_p(eng, "assets/tank_top.xpm");
	data->rot = 0.0f;
	return (1);
}

int	ft_loop(t_engine *eng, t_data *data, float et)
{
	(void)et;
	if (eng->keys[XK_Left])
		data->rot += 0.01f;
	if (eng->keys[XK_Right])
		data->rot -= 0.01f;
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
	ft_put_sprite(eng, data->spr[0], ft_v2i(0, 0));
	for (int i = 0; i < 40; i++)
	{
		ft_circle(eng, ft_v2i(120, 180 - i), 20, ft_color_d(0xFFE8FF));
		ft_circle(eng, ft_v2i(140, 160 - i), 20, ft_color_d(0x00E8FF));
	}
	//ft_v2i(eng->mouse_x, eng->mouse_y)
	ft_put_sprite_r(eng, data->spr[1], ft_v2i(100, 100), ft_v2i(33, 27), data->rot);
	ft_get_border(eng, data->spr[1], ft_v2i(100, 100), ft_v2i(33, 27), data->rot);
	//ft_put_sprite_r(eng, data->spr[2], ft_v2i(eng->mouse_x, eng->mouse_y), ft_v2i(17, 15), data->rot * 1.4);
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
