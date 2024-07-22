#include "generator.h"
#include "engine.h"


static void _recurs(t_generator *const gen, t_rect rect, int depth);

static void _recurs_x(t_generator *const gen, t_rect rect, int depth)
{
	t_v2i const	pos = rect.pos;
	t_v2i const	dim = rect.dim;

	if (rect.dim[1] < 3)
		return ;

	int random_wall = rand() % ((dim[0] - (dim[0] & 1)) / 2) * 2;
	int random_door = rand() % ((dim[1] - (dim[1] & 1)) / 2) * 2 + 1;

	printf("	In X: pos:[%d:%d] dim:[%d,%d]\n	Wall:%d\n", pos[0], pos[1], dim[0], dim[1], random_wall);

	for (int i = 0; i < dim[1]; i++)
		generator_set_tile(gen, (t_v2i){pos[0] + random_wall, pos[1] + i}, &(t_gen_tile){'1'});
	generator_set_tile(gen, (t_v2i){pos[0] + random_wall, pos[1] + random_door}, &(t_gen_tile){'0'});

	_recurs(gen, (t_rect){pos, {random_wall, dim[1]}}, depth + 1);
	_recurs(gen, (t_rect){{pos[0] + random_wall, pos[1]}, {dim[0] - random_wall, dim[1]}}, depth + 1);
}

static void _recurs_y(t_generator *const gen, t_rect rect, int depth)
{
	t_v2i const	pos = rect.pos;
	t_v2i const	dim = rect.dim;

	if (rect.dim[0] < 3)
		return ;

	int random_wall = rand() % ((dim[1] - (dim[1] & 1)) / 2) * 2;
	int random_door = rand() % ((dim[0] - (dim[0] & 1)) / 2) * 2 + 1;

	printf("	In Y: pos:[%d:%d] dim:[%d,%d]\n	Wall:%d\n", pos[0], pos[1], dim[0], dim[1], random_wall);

	for (int i = 0; i < dim[0]; i++)
		generator_set_tile(gen, (t_v2i){pos[0] + i, pos[1] + random_wall}, &(t_gen_tile){'1'});
	generator_set_tile(gen, (t_v2i){pos[0] + random_door, pos[1] + random_wall}, &(t_gen_tile){'0'});

	_recurs(gen, (t_rect){pos, {dim[0], random_wall}}, depth + 1);
	_recurs(gen, (t_rect){{pos[0], pos[1] + random_wall}, {dim[0], dim[1] - random_wall}}, depth + 1);
}


static void _recurs(t_generator *const gen, t_rect rect, int depth)
{
	if (rect.dim[0] < 4 && rect.dim[1] < 4)
		return ;

	if (rect.dim[0] > rect.dim[1])
		_recurs_x(gen, rect, depth);
	else if (rect.dim[0] <= rect.dim[1])
		_recurs_y(gen, rect, depth);
}


void	generator_gen_recurs(t_generator *const gen, int seed)
{
	srand(seed);

	// set map to zero
	ft_memset(gen->tiles.data, '0', gen->tiles.size * gen->tiles.type_size);

	_recurs(gen, (t_rect){{1, 1}, gen->size - 2}, 0);

	for (int y = 0; y < gen->size[1]; y++)
		for (int x = 0; x < gen->size[0]; x++)
			if (x == 0 || x == gen->size[0] - 1 || y == 0 || y == gen->size[1] - 1)
				generator_set_tile(gen, (t_v2i){x, y}, &(t_gen_tile){'1'});

	generator_set_tile(gen, (t_v2i){1, 1}, &(t_gen_tile){'P'});
}
