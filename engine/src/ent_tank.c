#include "game.h"

static int	_ft_tank_display(t_entity *self, t_data *game)
{
	t_length	i;
	t_dat_tank	*dat;

	dat = self->data;
	i = 0;
	while (i < 10)
	{
		ft_put_sprite_r(game->eng, game->spr[0], ft_v2i(dat->pos.x -
			game->cam.pos.x, dat->pos.y - game->cam.pos.y - i),
			ft_v2i(33, 27), dat->base_rot);
		i++;
	}
	i = 0;
	while (i < 3)
	{
		ft_put_sprite_r(game->eng, game->spr[1], ft_v2i(dat->pos.x -
			game->cam.pos.x, dat->pos.y - game->cam.pos.y - 10 - i),
			ft_v2i(17, 15), dat->top_rot);
		i++;
	}
	ft_circle(game->eng, ft_v2i(dat->pos.x -
		game->cam.pos.x, dat->pos.y - game->cam.pos.y), 100, ft_color_d(0x0F0000));
	ft_circle(game->eng, ft_v2i(dat->pos.x -
		game->cam.pos.x, dat->pos.y - game->cam.pos.y), 175, ft_color_d(0x000F00));
	ft_circle(game->eng, ft_v2i(dat->pos.x -
		game->cam.pos.x, dat->pos.y - game->cam.pos.y), 300, ft_color_d(0x00000F));
	ft_put_sprite_r(game->eng, game->spr[15], ft_v2i(game->eng->mouse_x, game->eng->mouse_y),
		ft_v2i(28, 1), dat->top_rot);
	return (1);
}

static void	_ft_tank_update2(t_entity *self, t_data *game, float dt)
{
	t_dat_tank	*dat;

	dat = self->data;
	dat->acc = sinf(fabsf(ft_v2fdot(dat->dir, dat->ine)) * M_PI_2);
	dat->vel = dat->vel * 0.96f * (dat->acc * dat->acc);
	dat->vel = ft_min(100, ft_max(-70, dat->vel));
	dat->pos = ft_v2fadd(dat->pos, ft_v2fmul(dat->ine, dat->vel * dt));
	game->cam.pos = ft_v2i(dat->pos.x - game->cam.dim.x / 2,
		dat->pos.y - game->cam.dim.y / 2);
	dat->top_rot = -atan2((game->cam.pos.x + (int)game->eng->mouse_x) -
		dat->pos.x, (game->cam.pos.y + (int)game->eng->mouse_y) - dat->pos.y + 12)
		+ M_PI_2;
	if (game->eng->mouse[1] && dat->fire_cool >= 0.125f / 2)
	{
		ft_vector_add(game->map.entities,
			ft_bullet_create(game, 1, ft_v2fadd(dat->pos, 
			ft_v2fadd(ft_v2fr(dat->top_rot, 35),
			ft_v2fr(dat->top_rot - M_PI_2, 10))),
			dat->top_rot + ((float)rand() / RAND_MAX - 0.5f) * 0.30));
		dat->fire_cool = 0.0f;
	}
	if (game->eng->mouse[3] && dat->fire_cool >= 4.0f)
	{
		ft_vector_add(game->map.entities,
			ft_shell_create(game, ft_v2fadd(dat->pos,
			ft_v2fr(dat->top_rot, 50)),
			dat->top_rot));
		dat->fire_cool = 0.0f;
	}
}

static int	_ft_tank_update(t_entity *self, t_data *game, float dt)
{
	t_dat_tank	*dat;

	dat = self->data;
	if (game->eng->keys[XK_a])
		dat->base_rot -= M_PI * dt * (1.0f - dat->vel / 150.0f);
	if (game->eng->keys[XK_d])
		dat->base_rot += M_PI * dt * (1.0f - dat->vel / 150.0f);
	dat->dir = ft_v2fr(dat->base_rot, 1.0f);
	if (game->eng->keys[XK_w])
	{
		dat->ine = ft_v2fmul(dat->dir, 1);
		dat->vel += 8.0f;
	}
	if (game->eng->keys[XK_s])
	{
		dat->ine = ft_v2fmul(dat->dir, -1);
		dat->vel += 3.0f;
	}
	dat->fire_cool += dt;
	_ft_tank_update2(self, game, dt);
	return (1);
}

static int	_ft_tank_destroy(t_entity *self, t_data *game)
{
	(void)game;
	free((t_entity *)self->data);
	free((t_entity *)self);
	return (1);
}

t_entity	*ft_tank_create(t_data *game, t_v2f pos)
{
	(void)game;
	t_entity	*ent;
	t_dat_tank	*data;

	ent = malloc(sizeof(t_entity));
	data = malloc(sizeof(t_dat_tank));
	data->pos = pos;
	data->ine = ft_v2f(0, 0);
	data->dir = ft_v2f(0, 0);
	data->acc = 0.0f;
	data->vel = 0.0f;
	data->base_rot = 0.0f;
	data->top_rot = 0.0f;
	data->fire_cool = 0.0f;
	ent->data = data;
	ent->display = &_ft_tank_display;
	ent->update = &_ft_tank_update;
	ent->destroy = &_ft_tank_destroy;
	ent->alive = 1;
    return (ent);
}
