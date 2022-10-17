#include "vec2.h"

t_v2i	ft_v2i(int x, int y)
{
	t_v2i	a;

	a.x = x;
	a.y = y;
	return (a);
}

t_v2i	ft_v2iadd(t_v2i a, t_v2i b)
{
	return (ft_v2i(a.x + b.x, a.y + b.y));
}

t_v2i	ft_v2isub(t_v2i a, t_v2i b)
{
	return (ft_v2i(a.x - b.x, a.y - b.y));
}

t_v2i	ft_v2imul(t_v2i a, float n)
{
	return (ft_v2i(a.x * n, a.y * n));
}

t_v2i	ft_v2idiv(t_v2i a, float n)
{
	return (ft_v2i(a.x / n, a.y / n));
}
