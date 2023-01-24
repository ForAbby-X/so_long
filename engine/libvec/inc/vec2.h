/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 17:27:32 by alde-fre          #+#    #+#             */
/*   Updated: 2022/12/23 18:49:00 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC2_H
# define VEC2_H

# include <math.h>

typedef float			t_v2f __attribute__((vector_size (8)));
typedef unsigned int	t_v2u __attribute__((vector_size (8)));
typedef int				t_v2i __attribute__((vector_size (8)));

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
