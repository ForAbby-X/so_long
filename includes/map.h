#ifndef MAP_H
# define MAP_H

#include "engine.h"
# include "../libvector/inc/vector.h"

typedef struct s_map	t_map;
typedef struct s_cell	t_cell;
typedef struct s_camera	t_camera;
typedef struct s_entity	t_entity;

int		ft_get_map(t_map *map, t_v2i pos);
void	ft_init_map(t_engine *eng, t_map *map, t_v2i size);
void	ft_destroy_map(t_map *map);
void	ft_put_map(t_engine *eng, t_camera cam, t_map *map);

t_v2i	ft_crd_sw(t_v2i screen);
t_v2i	ft_crd_ws(t_v2i world);

struct	s_map
{
	int			*data;
	t_v2i		size;
	t_sprite	*walls[18];
	t_vector	*entities;
};

struct	s_cell
{
	int	wall;
	int	ground;
};

struct	s_camera
{
	t_v2i	pos;
	t_v2i	dim;
};

struct	s_entity
{
	t_v2f	pos;
	t_v2f	dir;
	t_color	col;

};


#endif
