
#include "generator.h"

int		gen_tile_init(t_gen_tile *const gen, char *data, t_v2i size)
{
	gen->data = data;
	gen->size = size;
	return (0);
}

void	gen_tile_destroy(t_gen_tile *const gen)
{
	(void)gen;
}



int	generator_init(t_generator *const gen)
{
	(void)gen;
	// gen->tile_panel = vector_create(sizeof(t_tile));
	return (0);
}

void	generator_destroy(t_generator *const gen)
{
	(void)gen;
}
