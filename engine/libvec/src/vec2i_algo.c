#include "vec2.h"

t_v2i	ft_v2irot(t_v2i a, float r)
{
	t_v2i	b;
	float	c;
	float	s;

	c = cosf(r);
	s = sinf(r);
	b.x = a.x * c - a.y * s;
	b.y = a.x * s + a.y * c;
	return (b);
}
