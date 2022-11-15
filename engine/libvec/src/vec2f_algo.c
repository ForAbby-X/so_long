#include "vec2.h"

t_v2f	ft_v2fr(float r, float d)
{
	return (ft_v2f(cosf(r) * d, sinf(r) * d));
}

float	ft_v2fmag(t_v2f a)
{
	return (sqrtf(a.x * a.x + a.y * a.y));
}

float	ft_v2fdot(t_v2f a, t_v2f b)
{
	return (a.x * b.x + a.y * b.y);
}

float	ft_v2fcross(t_v2f a, t_v2f b)
{
	return (a.x * b.y - a.y * b.x);
}

t_v2f	ft_v2fnorm(t_v2f a, float n)
{
	float	mag;

	mag = ft_v2fmag(a);
	if (mag == 0.0f)
		return (ft_v2f(0.0f, 0.0f));
	return (ft_v2fmul(ft_v2fdiv(a, mag), n));
}
