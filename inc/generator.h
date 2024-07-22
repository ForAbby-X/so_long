#ifndef GENERATOR_H
# define GENERATOR_H

# include "vector.h"
# include "vec2.h"


// # TYPE DEFINITIONS
typedef struct	s_gen_tile	t_gen_tile;
typedef struct	s_generator	t_generator;

// # PROTOTYPES
int		gen_tile_init(t_gen_tile *const tile, int value);
void	gen_tile_destroy(t_gen_tile *const tile);


int		generator_init(t_generator *const gen, t_v2i const size);
void	generator_destroy(t_generator *const gen);

void	generator_set_tile(t_generator *const gen, t_v2i pos, t_gen_tile *const tile);
int		generator_get_tile(t_generator *const gen, t_v2i pos);

void	generator_gen_recurs(t_generator *const gen, int seed);
void	generator_gen_rooms(t_generator *const gen, int seed);


// # GLOBAL VARIABLES
// t_vector	g_tile_panel;


// # STRUCTURES
struct s_gen_tile
{
	char	value;
};

struct s_generator
{
	t_vector	tiles;
	t_v2i		size;

	// t_gen_tile	tile;
};

#endif