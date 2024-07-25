#include "generator.h"
#include "engine.h"

typedef struct s_room t_room;

////////////// ROOMS ////////////////

struct s_room
{
	t_v2f pos;
	t_v2f dim;
	t_vector neigbhors;
};

void inline room_init(t_room *const room, t_v2f pos, t_v2f dim)
{
	room->pos = pos;
	room->dim = dim;
	room->neigbhors = vector_create(sizeof(t_room *));
}

void room_destroy(t_object data)
{
	t_room *const room = data;
	vector_destroy(&room->neigbhors);
}

////////////////////////////////////

// aabb collision detection
int is_colliding(t_room room, t_room other_room)
{
	room.pos -= 1.0f;
	room.dim += 2.0f;

	other_room.pos -= 1.0f;
	other_room.dim += 2.0f;

	if (room.pos[0] < other_room.pos[0] + other_room.dim[0] &&
		room.pos[0] + room.dim[0] > other_room.pos[0] &&
		room.pos[1] < other_room.pos[1] + other_room.dim[1] &&
		room.pos[1] + room.dim[1] > other_room.pos[1])
		return 1;
	return 0;
}

int is_outside_map(t_room *room, t_v2i size)
{
	return (room->pos[0] < 0 || room->pos[0] + room->dim[0] >= size[0] ||
			room->pos[1] < 0 || room->pos[1] + room->dim[1] >= size[1]);
}

void move_inside_map(t_room *room, t_v2i size)
{
	if (room->pos[0] < 1)
		room->pos[0] = 1;
	if (room->pos[0] + room->dim[0] >= size[0] - 1)
		room->pos[0] = size[0] - room->dim[0] - 1;
	if (room->pos[1] < 1)
		room->pos[1] = 1;
	if (room->pos[1] + room->dim[1] >= size[1] - 1)
		room->pos[1] = size[1] - room->dim[1] - 1;
}

void move_outside_room(t_room *room, t_room *other_room)
{
	float displacement_fact = 2.5f;

	float x = ((float)room->pos[0] + room->dim[0] / 2.0f) - ((float)other_room->pos[0] + other_room->dim[0] / 2.0f);
	float y = ((float)room->pos[1] + room->dim[1] / 2.0f) - ((float)other_room->pos[1] + other_room->dim[1] / 2.0f);
	float max = fmaxf(room->dim[0], fmaxf(room->dim[1], fmaxf(other_room->dim[0], other_room->dim[1])));

	x = x / max * displacement_fact * 0.5f;
	y = y / max * displacement_fact * 0.5f;

	// printf("About to displace room %f %f\n", x, y);

	room->pos[0] += x;
	room->pos[1] += y;
	other_room->pos[0] -= x;
	other_room->pos[1] -= y;
}

void _push_rooms_appart(t_generator *const gen, t_vector *const rooms)
{
	int flag = 0;

	while (flag == 0)
	{
		flag = 1;
		for (t_length i = 0; i < rooms->size; i++)
		{
			t_room *room = vector_get(rooms, i);

			// Check collision with other rooms
			for (t_length j = 0; j < rooms->size; j++)
			{
				if (i == j)
					continue;
				t_room *other_room = vector_get(rooms, j);

				if (is_outside_map(room, gen->size))
				{
					move_inside_map(room, gen->size);
					flag = 0;
				}

				if (is_colliding(*room, *other_room))
				{
					move_outside_room(room, other_room);
					flag = 0;
				}
			}
		}
	}
}

// calculateNearestNeighbours() {
//     for(let i = 0; i < this.rooms.length; i++) {

//         let distances = [];

//         for(let j = 0; j < this.rooms.length; j++) {
//             if(i == j) {
//                 continue;
//             }
//             const d = this.rooms[i].center().subtract(this.rooms[j].center()).lengthSquared();
//             distances.push([i, j, d]);
//         }

//         distances.sort((first, second) => {
//             return first[2] - second[2];
//         });

//         for(let k = 0; k < this.nearestNeighbours; k++) {
//             const neighbour = this.rooms[distances[k][1]];
//             this.rooms[distances[k][0]].neighbours.push(neighbour);
//             this.graph.addEdge(...distances[k]);
//         }
//     }
// }

typedef struct s_edge
{
	t_room *from;
	t_room *to;
	float weight;
} t_edge;

int edge_cmp(void *ac, void *bc)
{
	t_edge *a = ac;
	t_edge *b = bc;

	return (a->weight - b->weight);
}

// generate neareste k-nearest neighbor graphs for rooms
void _gen_calculate_nearest_neighbors(t_vector *const rooms)
{
	for (t_length i = 0; i < rooms->size; i++)
	{
		t_room *room = vector_get(rooms, i);

		t_vector edges = vector_create(sizeof(t_edge));
		if (!edges.data)
			return;

		for (t_length j = 0; j < rooms->size; j++)
		{
			if (i == j)
				continue;
			t_room *other_room = vector_get(rooms, j);

			// check if duplicate
			int duplicate = 0;
			for (t_length k = 0; k < edges.size; k++)
			{
				t_edge *edge = vector_get(&edges, k);
				if (edge->from == other_room && edge->to == room)
				{
					duplicate = 1;
					break;
				}
				if (edge->from == room && edge->to == other_room)
				{
					duplicate = 1;
					break;
				}
			}
			if (duplicate)
				continue;

			t_v2f d = other_room->pos + other_room->dim / 2.f - room->pos + room->dim / 2.f;
			float dist = d[0] * d[0] + d[1] * d[1];
			vector_addback(&edges, &(t_edge){room, other_room, dist});
		}

		qsort(edges.data, edges.size, sizeof(t_edge), (__compar_fn_t)&edge_cmp);

		for (t_length k = 0; k < (t_length)ft_min(edges.size, 3); k++)
		{
			t_edge *dist = vector_get(&edges, k);

			vector_addback(&room->neigbhors, &dist->to);
		}

		// printf("Room %d has %u neighbors\n", i, room->neigbhors.size);

		vector_destroy(&edges);
	}
}

// put rooms on the map and connect them with corridors between neighbors
 void _gen_put_rooms(t_generator *const gen, t_vector *const rooms)
{
	printf("Putting rooms...\n");
	for (t_length i = 0; i < rooms->size; i++)
	{
		t_room *room = vector_get(rooms, i);

		// put room on the map
		for (t_length x = room->pos[0]; x < room->pos[0] + room->dim[0]; x++)
			for (t_length y = room->pos[1]; y < room->pos[1] + room->dim[1]; y++)
				generator_set_tile(gen, (t_v2i){x, y}, &(t_gen_tile){'0'});
	}

	printf("Putting corridors...\n");
	for (t_length i = 0; i < rooms->size; i++)
	{
		t_room *room = vector_get(rooms, i);
		// connect room with neighbors
		for (t_length j = 0; j < room->neigbhors.size; j++)
		{
			t_room *other_room = *(t_room **)vector_get(&room->neigbhors, j);
			if (other_room)
			{
				// connect rooms with corridors
				t_v2i start = (t_v2i){
					room->pos[0] + room->dim[0] / 2.0f,
					room->pos[1] + room->dim[1] / 2.0f};
				t_v2i end = (t_v2i){
					other_room->pos[0] + other_room->dim[0] / 2.0f,
					other_room->pos[1] + other_room->dim[1] / 2.0f};

				t_v2f dir = (t_v2f){
					end[0] - start[0],
					end[1] - start[1]};
				float max = fmaxf(fabsf(dir[0]), fabsf(dir[1]));
				dir = dir / max;

				t_v2f pos = (t_v2f){start[0], start[1]};
				while (max > 0.f)
				{
					pos += dir;
					for (int i = -1; i <= 1; i++)
						for (int j = -1; j <= 1; j++)
							generator_set_tile(gen, (t_v2i){(int)pos[0] + i, (int)pos[1] + j}, &(t_gen_tile){'0'});
					--max;
				}
			}
		}
	}
}

 void _gen_rand_rooms_and_separate(t_generator *const gen)
{
	t_vector rooms = vector_create(sizeof(t_room));
	if (!rooms.data)
		return;

	int const room_count = 80;
	for (t_length i = 0; i < room_count; i++)
	{
		t_room room;
		room_init(&room, (t_v2f){rand() % gen->size[0], rand() % gen->size[1]}, (t_v2f){rand() % 5 + 5, rand() % 5 + 5});
		vector_addback(&rooms, &room);

		printf("Room %d: pos: [%f;%f], dim: [%f;%f]\n", i, room.pos[0], room.pos[1], room.dim[0], room.dim[1]);
	}

	_push_rooms_appart(gen, &rooms);
	_gen_calculate_nearest_neighbors(&rooms);
	_gen_put_rooms(gen, &rooms);

	t_room *spawn = vector_get(&rooms, 0);

	t_v2i pos = (t_v2i){spawn->pos[0] + spawn->dim[0] / 2, spawn->pos[1] + spawn->dim[1] / 2};
	generator_set_tile(gen, pos, &(t_gen_tile){'P'});

	t_room *end = vector_get(&rooms, rooms.size - 1);
	pos = (t_v2i){end->pos[0] + end->dim[0] / 2, end->pos[1] + end->dim[1] / 2};
	generator_set_tile(gen, pos, &(t_gen_tile){'E'});

	vector_for_each(&rooms, &room_destroy);
	vector_destroy(&rooms);
}

void generator_gen_rooms(t_generator *const gen, int seed)
{
	srand(seed);

	// set map to zero
	ft_memset(gen->tiles.data, '1', gen->tiles.size * gen->tiles.type_size);

	_gen_rand_rooms_and_separate(gen);
}
