/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 09:35:53 by alde-fre          #+#    #+#             */
/*   Updated: 2023/02/02 14:17:54 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# define SPRITES_NBR 50

# include "engine.h"
# include "vector.h"

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <dirent.h>

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
typedef struct s_dat_coin		t_dat_coin;
typedef struct s_dat_exit		t_dat_exit;
typedef struct s_dat_object		t_dat_object;

struct	s_map
{
	char		*data;
	t_v2i		size;
	t_vector	*entities;
	t_length	active_nbr;
	t_vector	*particles;
	t_sprite	*background;
	char		*name;
	float		score;
};

struct	s_camera
{
	t_v2i	pos;
	t_v2i	dim;
};

/* UTILS */
int			ft_check_col(t_color a, t_color b, int diff);
int			ft_check_col_zone(t_sprite *spr, t_v2i pos, t_color b, int diff);
int			ft_get_obj_prob(t_map *map, t_v2i pos);
void		ft_explosion(t_data *game, t_v2f pos, float power);

/* MENU */
void		ft_menu(t_data *game, t_vector	*maps);
void		ft_entry(t_data *game);
void		ft_exit(t_data *game, int crates, float meter);
void		ft_death(t_data *game);

char		ft_get_map(t_map *map, t_v2i pos);
int			ft_init_game(t_engine *eng, t_data *data);
void		ft_destroy_game(t_data *game);

void		ft_ent_check_activ(t_data *game);
int			ft_move_toward(t_v2f pos, t_v2f target, float speed, float r);

int			ft_game_render(t_data *data);
void		ft_game_render_ui(t_data *game);
int			ft_game_render_map(t_data *data);
int			ft_game_render_ent(t_data *data);
int			ft_game_update_ent(t_data *data, float dt);

int			ft_game_all_par(t_data *data, float dt);

/* MAP */
t_map		*ft_map_create(t_data *game, char *data, t_v2i size, char *name);
void		ft_maps_destroy(t_data *game);
void		ft_map_destroy(t_data *game, t_map *map);

void		ft_map_load(t_data *game, t_map *map);
void		ft_map_unload(t_data *game);

/* PARSING */
t_vector	*ft_pars_folder(t_data *game);
t_map		*ft_pars_file(t_data *game, char *str);

int			ft_check_map(t_map *map);

/* PARTICLES */
void		ft_emmit_sparks(t_data *game, t_length nb, t_v2f pos, float rot);
void		ft_emmit_blood(t_data *game, t_length nb, t_v2f pos, float rot);
void		ft_emmit_pool_blood(t_data *game, t_length nb, t_v2f pos);
void		ft_emmit_smoke_pipe(t_data *game, t_length nb, t_v2f pos);
void		ft_emmit_wood(t_data *game, t_v2f pos);

void		ft_emmit_explosion(t_data *game, t_v2f pos, float force);

/* RAYCASTING */
int			ft_cast_ray(t_data *game, t_v2f start, t_v2f end);

/* COLLISIONS */
void		ft_entity_collisions(t_data *game, float dt);

/* UUID */
long long	ft_get_uuid(void);

/* ENTITIES */
t_entity	*ft_ent_add(t_data *game, t_entity *ent);
t_entity	*ft_ent_get(t_data *game, t_length index);

void		ft_paint_tank(t_data *game, t_entity *tank, t_entity *enn_pos);

void		ft_damage_enn(t_data *game, t_entity *ent, float damage, float rot);

t_entity	*ft_tank_create(t_data *game, t_v2f pos);
t_entity	*ft_bullet_create(int type, t_v2f pos, float rot, t_uuid uuid);
t_entity	*ft_ennemy_create(t_v2f pos, float rot);
t_entity	*ft_shell_create(t_v2f pos, float rot);
t_entity	*ft_coin_create(t_v2f pos);
t_entity	*ft_exit_create(t_v2f pos);
t_entity	*ft_object_create(int type, t_v2f pos);

/* STRUCTURES */
struct s_data
{
	t_engine	*eng;
	t_sprite	*spr[SPRITES_NBR];
	t_map		*map;
	t_vector	*maps;
	t_camera	cam;
	t_dat_tank	*dplay;
	t_entity	*eplay;
	uint8_t		state;
	float		state_time;
	float		shake;
	float		time;
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
	void	(*display)(t_entity *self, t_data *game);
	void	(*update)(t_entity *self, t_data *game, float delta_time);
	void	(*destroy)(t_entity *self, t_data *game);
	t_v2f	pos;
	t_v2f	dir;
	float	rot;
	float	radius;
	float	pressure;
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
	t_v2f		acc;
	t_v2f		vel;
	t_v2f		trac;
	t_v2f		drag;
	t_v2f		bloody;
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

struct s_dat_coin
{
	float	time;
};

struct s_dat_exit
{
	int		is_open;
	float	time;
};

struct s_dat_object
{
	int		type;
	float	health;
};

#endif
