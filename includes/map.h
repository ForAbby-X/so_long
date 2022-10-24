#ifndef MAP_H
# define MAP_H

#include "engine.h"

typedef struct s_map	t_map;
typedef struct s_cell	t_cell;

void	ft_init_map(t_engine *eng, t_map *map, t_v2i size);
void	ft_destroy_map(t_map *map);
void	ft_put_map(t_engine *eng, t_map *map);
int	ft_get_map(t_map *map, t_v2i pos);

struct	s_map
{
	t_cell		*data;
	t_v2i		size;
	t_sprite	*walls[16];
};

struct	s_cell
{
	int	wall;
	int	ground;
};

#endif
