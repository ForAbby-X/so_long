#ifndef GAME_H
# define GAME_H

# include "engine.h"
# include "vector.h"

typedef struct s_map	t_map;
typedef struct s_cell	t_cell;
typedef struct s_camera	t_camera;
typedef struct s_entity	t_entity;

struct	s_map
{
	int			*data;
	t_v2i		size;
	t_sprite	*walls[19];
	t_vector	*entities;
	t_vector	*bullets;
};

struct	s_camera
{
	t_v2i	pos;
	t_v2i	dim;
};

int		ft_get_map(t_map *map, t_v2i pos);
void	ft_init_map(t_engine *eng, t_map *map, t_v2i size);
void	ft_destroy_map(t_map *map);
void	ft_put_map(t_engine *eng, t_camera cam, t_map *map);

int		ft_init_game(t_engine *eng, t_data *data);

int		ft_game_render(t_data *data);
int		ft_game_rend_map(t_data *data);
int		ft_game_rend_ent(t_data *data);
int		ft_game_upd_ent(t_data *data, float dt);

/* ENTITY */
/* TANK */
t_entity	*ft_tank_create(t_data  *game, t_v2f pos);

/* STRUCTURES */
struct s_data
{
	t_engine	*eng;
	t_sprite	*spr[16];
	t_map		map;
	t_camera	cam;
};

struct	s_cell
{
	int	wall;
	int	ground;
};

struct	s_entity
{
	int		(*display)(const t_entity *self, t_data *game);
	int		(*update)(const t_entity *self, t_data *game, float delta_time);
	int		(*destroy)(const t_entity *self, t_data *game);
	void	*data;
	int		alive;
};

/* ENTITIES */
typedef struct  s_dat_tank
{
    t_v2f		ine;
	t_v2f		pos;
	t_v2f		dir;
	float		acc;
	float		vel;
	float		base_rot;
	float		top_rot;
}   t_dat_tank;

#endif

