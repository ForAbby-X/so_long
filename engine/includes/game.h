#ifndef GAME_H
# define GAME_H

# include "engine.h"
# include "vector.h"

typedef struct s_map	t_map;
typedef struct s_cell	t_cell;
typedef struct s_camera	t_camera;
typedef struct s_entity	t_entity;

typedef struct s_dat_tank	t_dat_tank;
typedef struct s_dat_bullet	t_dat_bullet;
typedef struct s_dat_enn_base	t_dat_enn_base;
typedef struct s_dat_shell	t_dat_shell;

struct	s_map
{
	int			*data;
	t_v2i		size;
	t_vector	*entities;
};

struct	s_camera
{
	t_v2i	pos;
	t_v2i	dim;
};

int		ft_get_map(t_map *map, t_v2i pos);
int		ft_init_game(t_engine *eng, t_data *data);

int		ft_game_render(t_data *data);
void	ft_game_render_ui(t_data *game);
int		ft_game_render_map(t_data *data);
int		ft_game_render_ent(t_data *data);
int		ft_game_upd_ent(t_data *data, float dt);

/* ENTITIES */
t_entity	*ft_tank_create(t_data  *game, t_v2f pos);
t_entity	*ft_bullet_create(t_data *game, int type, t_v2f pos, float rot);
t_entity	*ft_ennemy_create(t_data *game, t_v2f pos, float rot);
t_entity	*ft_shell_create(t_data *game, t_v2f pos, float rot);

/* STRUCTURES */
struct s_data
{
	t_engine	*eng;
	t_sprite	*spr[32];
	t_map		map;
	t_camera	cam;
	t_dat_tank	*player;
};

struct	s_cell
{
	int	wall;
	int	ground;
};

struct	s_entity
{
	int		(*display)(t_entity *self, t_data *game);
	int		(*update)(t_entity *self, t_data *game, float delta_time);
	int		(*destroy)(t_entity *self, t_data *game);
	void	*data;
	int		type;
	int		alive;
};

/* ENTITIES */
struct  s_dat_tank
{
    t_v2f		ine;
	t_v2f		pos;
	t_v2f		dir;
	float		acc;
	float		vel;
	float		base_rot;
	float		top_rot;
	float		fire_cool;
};

struct  s_dat_bullet
{
	t_v2f	pos;
	t_v2f	dir;
	float	rot;
	int		type;
	float	time;
};

struct  s_dat_enn_base
{
	t_v2f	pos;
	t_v2f	dir;
	float	rot;
	float	time;
	float	health;
	float	max_health;
	float	fire_cool;
	int		state;
};

struct  s_dat_shell
{
	t_v2f	pos;
	t_v2f	dir;
	float	rot;
	float	time;
};

#endif

