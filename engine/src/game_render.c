#include "game.h"

int		ft_game_render(t_data *game)
{
	ft_game_rend_map(game);
	ft_game_rend_ent(game);
	ft_ui_render(game);
	return (1);
}

void	ft_ui_render(t_data *game)
{
	t_dat_tank	*dat;
	float		s;
	float		c;

	dat = ((t_entity *)ft_vector_get(game->map.entities, 0))->data;
	if (dat->fire_cool < 4.0f)
	{
		ft_rect(game->eng, ft_v2i(34, 4), ft_v2i(204, 24), ft_color_d(0xE0E0E0));
		ft_rect(game->eng, ft_v2i(36, 6), ft_v2i(ft_min(dat->fire_cool / 4.0f * 200, 200), 20),
			ft_color_d(0xE0AF00));
	}
	else
	{
		s = sinf(dat->fire_cool * 80) * 2;
		c = cosf(dat->fire_cool * 60.6) * 2;
		ft_rect(game->eng, ft_v2i(34 + s, 4 + c), ft_v2i(204, 24), ft_color_d(0x850606));
		ft_rect(game->eng, ft_v2i(36 + s, 6 + c), ft_v2i(ft_min(dat->fire_cool / 4.0f * 200, 200), 20),
			ft_color_d(0xE0AF00));
	}
	ft_put_sprite(game->eng, game->spr[18], ft_v2i(4, 4));
}

int		ft_game_rend_map(t_data *data)
{
	t_v2i	pos;
	t_v2i	rpos;
	t_v2i	wpos;

	pos.y = -1;
	while (pos.y <= data->cam.dim.y / 32 + 1)
	{
		pos.x = -1;
		while (pos.x <= data->cam.dim.x / 32 + 1)
		{
			rpos.x = (pos.x - (data->cam.pos.x / 32. - data->cam.pos.x / 32)) * 32;
			rpos.y = (pos.y - (data->cam.pos.y / 32. - data->cam.pos.y / 32)) * 32;
			wpos = ft_v2iadd(pos, ft_v2idiv(data->cam.pos, 32));
			ft_put_sprite(data->eng, data->spr[2], rpos);
			if (ft_get_map(&data->map, wpos))
			{
				if (ft_get_map(&data->map, ft_v2i(wpos.x, wpos.y + 1)))
					ft_put_sprite(data->eng, data->spr[4], rpos);
				else
					ft_put_sprite(data->eng, data->spr[3], rpos);
			}
			pos.x++;
		}
		pos.y++;
	}
	return (1);
}

int		ft_game_rend_ent(t_data *data)
{
	t_entity	*ent;
	t_length	i;

	i = 0;
	while (i < ft_vector_size(data->map.entities))
	{
		ent = (t_entity *)ft_vector_get(data->map.entities, i);
		ent->display(ent, data);
		i++;
	}
	return (1);
}

int		ft_game_upd_ent(t_data *data, float dt)
{
	t_entity	*ent;
	t_length	i;

	i = 0;
	while (i < ft_vector_size(data->map.entities))
	{
		ent = (t_entity *)ft_vector_get(data->map.entities, i);
		ent->update(ent, data, dt);
		i++;
	}
	i = 0;
	while (i < ft_vector_size(data->map.entities))
	{
		ent = (t_entity *)ft_vector_get(data->map.entities, i);
		if (ent->alive == 0)
		{
			ent->destroy(ent, data);
			ft_vector_rem(data->map.entities, i);
		}
		else
			i++;
	}
	return (1);
}
