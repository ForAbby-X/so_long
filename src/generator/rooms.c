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

void room_init(t_room *const room, t_v2f pos, t_v2f dim)
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

	return (a->weight > b->weight);
}

// generate minimum weight spanning tree
void _gen_calculate_nearest_neighbors(t_vector *const rooms)
{
	for (t_length i = 0; i < rooms->size - 1; i++)
	{
		t_room *room = vector_get(rooms, i);

		t_vector edges = vector_create(sizeof(t_edge));
		if (!edges.data)
			return;

		for (t_length j = 0; j < rooms->size; j++)
		{
			t_room *other_room = vector_get(rooms, j);

			if (other_room->neigbhors.size > 0 || i == j)
				continue;

			t_edge edge;
			edge.from = room;
			edge.to = other_room;
			edge.weight = ft_v2fmag(other_room->pos - room->pos);
			vector_addback(&edges, &edge);
		}

		qsort(edges.data, edges.size, edges.type_size, (__compar_fn_t)&edge_cmp);

		t_edge *edge = vector_get(&edges, 0);

		vector_addback(&room->neigbhors, &edge->to);

		vector_destroy(&edges);
	}
}

void plotLineWidth(t_generator *const gen, int x0, int y0, int x1, int y1, float wd)
{
	int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
	int err = dx - dy, e2, x2, y2; /* error value e_xy */
	float ed = dx + dy == 0 ? 1 : sqrt((float)dx * dx + (float)dy * dy);

	for (wd = (wd + 1) / 2;;)
	{ /* pixel loop */
		generator_set_tile(gen, (t_v2i){x0, y0}, &(t_gen_tile){'0'});
		e2 = err;
		x2 = x0;
		if (2 * e2 >= -dx)
		{ /* x step */
			for (e2 += dy, y2 = y0; e2 < ed * wd && (y1 != y2 || dx > dy); e2 += dx)
				generator_set_tile(gen, (t_v2i){x0, y2 += sy}, &(t_gen_tile){'0'});
			if (x0 == x1)
				break;
			e2 = err;
			err -= dy;
			x0 += sx;
		}
		if (2 * e2 <= dy)
		{ /* y step */
			for (e2 = dx - e2; e2 < ed * wd && (x1 != x2 || dx < dy); e2 += dy)
				generator_set_tile(gen, (t_v2i){x2 += sx, y0}, &(t_gen_tile){'0'});
			if (y0 == y1)
				break;
			err += dx;
			y0 += sy;
		}
	}
}



// put rooms on the map and connect them with corridors between neighbors
 void _gen_put_rooms(t_generator *const gen, t_vector *const rooms)
{
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
					plotLineWidth(gen, pos[0], pos[1], pos[0] + dir[0], pos[1] + dir[1], 4.f);
					--max;
				}
			}
		}
	}

	printf("Putting rooms...\n");
	for (t_length i = 0; i < rooms->size; i++)
	{
		t_room *room = vector_get(rooms, i);

		// put room on the map
		for (t_length x = room->pos[0]; x < room->pos[0] + room->dim[0]; x++)
			for (t_length y = room->pos[1]; y < room->pos[1] + room->dim[1]; y++)
				generator_set_tile(gen, (t_v2i){x, y}, &(t_gen_tile){'1'});
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
	t_v2i pos = (t_v2i){
		spawn->pos[0]  + (rand() % (int)(spawn->dim[0] - 2.f) + 1),
		spawn->pos[1]  + (rand() % (int)(spawn->dim[1] - 2.f) + 1)};
	generator_set_tile(gen, pos, &(t_gen_tile){'P'});

	t_room *end = vector_get(&rooms, rooms.size - 1);
	pos = (t_v2i){
		end->pos[0] + (rand() % (int)(end->dim[0] - 2.f) + 1),
		end->pos[1] + (rand() % (int)(end->dim[1] - 2.f) + 1)};
	generator_set_tile(gen, pos, &(t_gen_tile){'E'});

	vector_for_each(&rooms, &room_destroy);
	vector_destroy(&rooms);
}

void generator_gen_rooms(t_generator *const gen, int seed)
{
	srand(seed);

	// set map to zero
	ft_memset(gen->tiles.data, '#', gen->tiles.size * gen->tiles.type_size);

	_gen_rand_rooms_and_separate(gen);
}
