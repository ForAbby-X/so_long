#include "generator.h"
#include "engine.h"


// ddsfdf;

int is_colliding(t_rect *room, t_rect *other_room)
{

	if (room->pos[0] + room->dim[0] > other_room->pos[0] &&
		room->pos[0] < other_room->pos[0] + other_room->dim[0] &&
		room->pos[1] + room->dim[1] > other_room->pos[1] &&
		room->pos[1] < other_room->pos[1] + other_room->dim[1])
		return (1);
	return (0);
}

int is_outside_map(t_rect *room, t_v2i size)
{
	return (room->pos[0] < 0 || room->pos[0] + room->dim[0] >= size[0] ||
			room->pos[1] < 0 || room->pos[1] + room->dim[1] >= size[1]);
}

void move_inside_map(t_rect *room, t_v2i size)
{
	if (room->pos[0] < 0)
		room->pos[0] = 0;
	if (room->pos[0] + room->dim[0] >= size[0])
		room->pos[0] = size[0] - room->dim[0];
	if (room->pos[1] < 0)
		room->pos[1] = 0;
	if (room->pos[1] + room->dim[1] >= size[1])
		room->pos[1] = size[1] - room->dim[1];
}

void move_outside_room(t_rect *room, t_rect *other_room)
{
	int x = room->pos[0] - other_room->pos[0];
	int y = room->pos[1] - other_room->pos[1];

	if (x < 0)
		room->pos[0] -= x;
	else
		room->pos[0] += x;

	if (y < 0)
		room->pos[1] -= y;
	else
		room->pos[1] += y;
}

static void _push_rooms_appart(t_generator *const gen, t_vector *const rooms)
{
	for (t_length i = 0; i < rooms->size; i++)
	{
		t_rect *room = (t_rect *)vector_get(rooms, i);

		// Check collision with other rooms
		for (t_length j = 0; j < rooms->size; j++)
		{
			if (i == j)
				continue;
			t_rect *other_room = (t_rect *)vector_get(rooms, j);

			if (is_outside_map(room, gen->size))
				move_inside_map(room, gen->size);

			if (is_colliding(room, other_room))
				move_outside_room(room, other_room);
		}
	}
}

static void _gen_put_rooms(t_generator *const gen, t_vector *const rooms)
{
	for (t_length i = 0; i < rooms->size; i++)
	{
		t_rect *room = (t_rect *)vector_get(rooms, i);

		printf("Room %d: pos(%d, %d) dim(%d, %d)\n", i, room->pos[0], room->pos[1], room->dim[0], room->dim[1]);

		for (int y = room->pos[1]; y < room->pos[1] + room->dim[1]; y++)
			for (int x = room->pos[0]; x < room->pos[0] + room->dim[0]; x++)
				generator_set_tile(gen, (t_v2i){x, y}, &(t_gen_tile){'0'});
	}
}

static void _gen_rand_rooms_and_separate(t_generator *const gen)
{
	t_vector rooms = vector_create(sizeof(t_rect));
	if (!rooms.data)
		return;

	int const room_count = 30;
	for (t_length i = 0; i < room_count; i++)
	{
		t_rect room;
		room.pos = (t_v2i){rand() % gen->size[0], rand() % gen->size[1]};
		room.dim = (t_v2i){rand() % 10 + 5, rand() % 10 + 5};
		vector_addback(&rooms, &room);
	}

	_push_rooms_appart(gen, &rooms);

	_gen_put_rooms(gen, &rooms);

	vector_destroy(&rooms);
}

void generator_gen_rooms(t_generator *const gen, int seed)
{
	srand(seed);

	// set map to zero
	ft_memset(gen->tiles.data, '1', gen->tiles.size * gen->tiles.type_size);

	_gen_rand_rooms_and_separate(gen);


	generator_set_tile(gen, (t_v2i){1, 1}, &(t_gen_tile){'P'});
}
