#include "game.h"

static int	_ft_ennemy_display(t_entity *self, t_data *game)
{
	t_dat_enn_base	*dat;

	dat = self->data;
	ft_put_sprite_r(game->eng, game->spr[4], ft_v2i(dat->pos.x -
		game->cam.pos.x, dat->pos.y - game->cam.pos.y),
		ft_v2i(16, 16), dat->rot);
	return (1);
}

static int	_ft_ennemy_update(t_entity *self, t_data *game, float dt)
{
	(void)game;
	t_dat_enn_base	*dat;

	dat = self->data;
	dat->pos = ft_v2fadd(dat->pos, ft_v2fmul(dat->dir, dt));
	return (1);
}

static int	_ft_ennemy_destroy(t_entity *self, t_data *game)
{
	(void)game;
	free((t_entity *)self->data);
	free((t_entity *)self);
	return (1);
}

t_entity	*ft_ennemy_create(t_data *game, t_v2f pos, float rot)
{
	(void)game;
	t_entity	*ent;
	t_dat_enn_base	*data;

	ent = malloc(sizeof(t_entity));
	data = malloc(sizeof(t_dat_enn_base));
	data->pos = pos;
	data->dir = ft_v2fr(rot, 10);
	data->rot = rot;
	data->time = 0.0f;
	data->health = 100.0f;
	data->max_health = 100.0f;
	ent->data = data;
	ent->display = &_ft_ennemy_display;
	ent->update = &_ft_ennemy_update;
	ent->destroy = &_ft_ennemy_destroy;
	ent->alive = 1;
    return (ent);
}
