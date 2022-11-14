#include "game.h"

int		ft_game_render(t_data *data)
{
	ft_game_rend_map(data);
	ft_game_rend_ent(data);
	return (1);
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
				ft_put_sprite(data->eng, data->spr[3], rpos);
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
			printf("REMOVED [%p]\n", ent);
			ent->destroy(ent, data);
			ft_vector_rem(data->map.entities, i);
		}
		else
			i++;
	}
	return (1);
}
