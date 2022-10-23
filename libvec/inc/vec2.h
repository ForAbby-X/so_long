#ifndef VEC2_H
# define VEC2_H

# include <math.h>

typedef struct s_v2f	t_v2f;
typedef struct s_v2u	t_v2u;
typedef struct s_v2i	t_v2i;

// arithmetic
// FLOAT
t_v2f	ft_v2f(float x, float y);
t_v2f	ft_v2fadd(t_v2f a, t_v2f b);
t_v2f	ft_v2fsub(t_v2f a, t_v2f b);
t_v2f	ft_v2fmul(t_v2f a, float n);
t_v2f	ft_v2fdiv(t_v2f a, float n);

// INT
t_v2i	ft_v2i(int x, int y);
t_v2i	ft_v2iadd(t_v2i a, t_v2i b);
t_v2i	ft_v2isub(t_v2i a, t_v2i b);
t_v2i	ft_v2imul(t_v2i a, float n);
t_v2i	ft_v2idiv(t_v2i a, float n);

// algorithm
// FLOAT
t_v2f	ft_v2fr(float r, float d);
float	ft_v2fmag(t_v2f a);
float	ft_v2fdot(t_v2f a, t_v2f b);
float	ft_v2fcross(t_v2f a, t_v2f b);
t_v2f	ft_v2fnorm(t_v2f a, float n);

// INT
t_v2i	ft_v2irot(t_v2i a, float r);

struct s_v2f
{
	float	x;
	float	y;
};

struct s_v2u
{
	unsigned int	x;
	unsigned int	y;
};

struct s_v2i
{
	int	x;
	int	y;
};
#endif
