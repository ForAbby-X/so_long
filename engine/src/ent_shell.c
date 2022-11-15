#include "game.h"

static int	_ft_shell_display(t_entity *self, t_data *game)
{
	t_dat_shell	*dat;
	int			anim;

	dat = self->data;
	anim = ((int)(dat->time * 10)) % 3;
	ft_put_sprite_r(game->eng, game->spr[15 + anim], ft_v2i(dat->pos.x -
		game->cam.pos.x, dat->pos.y - game->cam.pos.y - 11),
		ft_v2i(4, 4), dat->rot);
	return (1);
}

static int	_ft_shell_update(t_entity *self, t_data *game, float dt)
{
	(void)game;
	t_dat_shell	*dat;

	dat = self->data;
	dat->pos = ft_v2fadd(dat->pos, ft_v2fmul(dat->dir, dt));
	dat->time += dt;
	self->alive = !(dat->time >= 2.0f);
	return (1);
}

static int	_ft_shell_destroy(t_entity *self, t_data *game)
{
	(void)game;
	free((t_entity *)self->data);
	free((t_entity *)self);
	return (1);
}

t_entity	*ft_shell_create(t_data *game, t_v2f pos, float rot)
{
	(void)game;
	t_entity		*ent;
	t_dat_shell	*data;

	ent = malloc(sizeof(t_entity));
	data = malloc(sizeof(t_dat_shell));
	data->pos = pos;
	data->dir = ft_v2fr(rot, 400);
	data->rot = rot;
	data->time = 0.0f;
	ent->data = data;
	ent->display = &_ft_shell_display;
	ent->update = &_ft_shell_update;
	ent->destroy = &_ft_shell_destroy;
	ent->alive = 1;
    return (ent);
}
