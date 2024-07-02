#ifndef GENERATOR_H
# define GENERATOR_H

# include "vector.h"
# include "vec2.h"

// # TYPE DEFINITIONS
typedef struct	s_gen_tile t_gen_tile;
typedef struct	s_generator t_generator;

// # PROTOTYPES
int		gen_tile_init(t_gen_tile *const gen, char *data, t_v2i size);
void	gen_tile_destroy(t_gen_tile *const gen);

int		generator_init(t_generator *const gen);
void	generator_destroy(t_generator *const gen);


// # GLOBAL VARIABLES
t_vector	g_tile_panel;


// # STRUCTURES
struct s_gen_tile
{
	char		*data;
	t_v2i		size;
};

struct s_generator
{
	t_vector	content;
};

#endif