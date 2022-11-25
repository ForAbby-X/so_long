/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 09:35:53 by alde-fre          #+#    #+#             */
/*   Updated: 2022/11/25 11:59:12 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "engine.h"
# include "vector.h"

typedef struct s_map			t_map;
typedef struct s_cell			t_cell;
typedef struct s_camera			t_camera;
typedef struct s_entity			t_entity;
typedef struct s_particle		t_particle;

typedef long long				t_uuid;

typedef struct s_dat_tank		t_dat_tank;
typedef struct s_dat_bullet		t_dat_bullet;
typedef struct s_dat_enn_base	t_dat_enn_base;
typedef struct s_dat_shell		t_dat_shell;

struct	s_map
{
	int			*data;
	t_v2i		size;
	t_vector	*entities;
	t_vector	*particles;
	t_sprite	*background;
};

struct	s_camera
{
	t_v2i	pos;
	t_v2i	dim;
};

int			ft_get_map(t_map *map, t_v2i pos);
int			ft_init_game(t_engine *eng, t_data *data);
void		ft_destroy_game(t_data *game);

int			ft_game_render(t_data *data);
void		ft_game_render_ui(t_data *game);
int			ft_game_render_map(t_data *data);
int			ft_game_render_ent(t_data *data);
int			ft_game_upd_ent(t_data *data, float dt);

int			ft_game_all_par(t_data *data, float dt);

/* DRAWING */
int			ft_drawh(t_data *game, t_v2i pos, t_color color, uint8_t height);
int			ft_put_sprite_h(t_data *game, t_sprite *spr, t_v2i pos);
int			ft_put_sprite_rh(t_data *game, t_sprite *spr,
				t_v2i pos, t_v2i cen, float rot);

/* PARTICLES */
void		ft_emmit_sparks(t_data *game, t_length nb, t_v2f pos, float rot);
void		ft_emmit_blood(t_data *game, t_length nb, t_v2f pos, float rot);
void		ft_emmit_pool_blood(t_data *game, t_length nb, t_v2f pos);
void		ft_emmit_smoke_pipe(t_data *game, t_length nb, t_v2f pos);

/* RAYCASTING */
int			ft_cast_ray(t_data *game, t_v2f start, t_v2f end);

/* COLLISIONS */
void		ft_entity_collisions(t_data *game);

/* UUID */
long long	ft_get_uuid(void);

/* ENTITIES */
t_entity	*ft_ent_add(t_data *game, t_entity *ent);

void		ft_paint_tank(t_data *game, t_entity *tank, t_entity *enn_pos);

t_entity	*ft_tank_create(t_data *game, t_v2f pos);
t_entity	*ft_bullet_create(int type, t_v2f pos, float rot, t_uuid uuid);
t_entity	*ft_ennemy_create(t_v2f pos, float rot);
t_entity	*ft_shell_create(t_v2f pos, float rot);

/* STRUCTURES */
struct s_data
{
	t_engine	*eng;
	t_sprite	*spr[32];
	t_map		map;
	t_camera	cam;
	t_dat_tank	*dplay;
	t_entity	*eplay;
	float		shake;
};

struct	s_cell
{
	int	wall;
	int	ground;
};

struct	s_particle
{
	t_v2f		pos;
	t_v2f		dir;
	float		accel;
	float		time;
	float		life_time;
	t_sprite	*spr;
	t_v2i		off;
};

struct	s_entity
{
	int		(*display)(t_entity *self, t_data *game);
	int		(*update)(t_entity *self, t_data *game, float delta_time);
	int		(*destroy)(t_entity *self, t_data *game);
	t_v2f	pos;
	t_v2f	dir;
	float	rot;
	float	radius;
	void	*data;
	t_uuid	uuid;
	int		type;
	int		alive;
};

/* RAYCAST */
typedef struct s_ray
{
	t_v2f	dir;
	t_v2i	pos;
	t_v2f	side_dist;
	t_v2f	delta_dist;
	t_v2i	step;
}	t_ray;

/* ENTITIES */
struct s_dat_tank
{
	t_v2f		ine;
	float		acc;
	float		vel;
	float		top_rot;
	float		fire_cool;
	float		timer;
	t_sprite	*spr;
};

struct s_dat_bullet
{
	t_uuid	shooter_id;
	int		type;
	float	time;
};

struct s_dat_enn_base
{
	float	time;
	float	health;
	float	max_health;
	float	fire_cool;
	int		state;
};

struct s_dat_shell
{
	float	time;
};

#endif
