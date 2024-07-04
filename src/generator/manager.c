
#include "generator.h"

int		gen_tile_init(t_gen_tile *const tile, int value)
{
	tile->value = value;
	return (value);
}

void	gen_tile_destroy(t_gen_tile *const tile)
{
	(void)tile;
}



int	generator_init(t_generator *const gen, t_v2i const size)
{
	gen->tiles = vector_create(sizeof(t_gen_tile));
	if (!gen->tiles.data)
		return (1);
	vector_resize(&gen->tiles, size[0] * size[1]);
	gen->size = size;
	return (0);
}

void	generator_destroy(t_generator *const gen)
{
	vector_destroy(&gen->tiles);
}

void	generator_set_tile(t_generator *const gen, t_v2i pos, t_gen_tile *const tile)
{
	t_gen_tile	*ptr;

	ptr = vector_get(&gen->tiles, pos[0] + pos[1] * gen->size[0]);
	if (!ptr)
		return ;

	*ptr = *tile;
}

int		generator_get_tile(t_generator *const gen, t_v2i pos)
{
	t_gen_tile	*ptr;

	ptr = vector_get(&gen->tiles, pos[0] + pos[1] * gen->size[0]);
	if (!ptr)
		return (-1);

	return (ptr->value);
}
