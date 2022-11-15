#include "game.h"

static int	_ft_bullet_display(t_entity *self, t_data *game)
{
	t_dat_bullet	*dat;

	dat = self->data;
	ft_put_sprite_r(game->eng, game->spr[5 + dat->type], ft_v2i(dat->pos.x -
		game->cam.pos.x, dat->pos.y - game->cam.pos.y - 11),
		ft_v2i(28, 1), dat->rot);
	return (1);
}

static int	_ft_bullet_update(t_entity *self, t_data *game, float dt)
{
	(void)game;
	t_dat_bullet	*dat;	

	dat = self->data;
	dat->pos = ft_v2fadd(dat->pos, ft_v2fmul(dat->dir, dt));
	dat->time += dt;
	self->alive = !(dat->time >= 2.0f);
	return (1);
}

static int	_ft_bullet_destroy(t_entity *self, t_data *game)
{
	(void)game;
	free((t_entity *)self->data);
	free((t_entity *)self);
	return (1);
}

t_entity	*ft_bullet_create(t_data *game, int type, t_v2f pos, float rot)
{
	(void)game;
	t_entity		*ent;
	t_dat_bullet	*data;

	ent = malloc(sizeof(t_entity));
	data = malloc(sizeof(t_dat_bullet));
	data->pos = pos;
	data->dir = ft_v2fr(rot, 1000);
	data->type = type;
	data->rot = rot;
	data->time = 0.0f;
	ent->data = data;
	ent->display = &_ft_bullet_display;
	ent->update = &_ft_bullet_update;
	ent->destroy = &_ft_bullet_destroy;
	ent->alive = 1;
    return (ent);
}
