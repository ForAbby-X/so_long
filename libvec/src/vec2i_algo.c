#include "vec2.h"

t_v2i	ft_v2irot(t_v2i a, float r)
{
	t_v2i	b;

	b.x = a.x * cosf(r) - a.y * sinf(r);
	b.y = a.x * sinf(r) - a.y * cosf(r);
	return (b);
}
