/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 17:27:32 by alde-fre          #+#    #+#             */
/*   Updated: 2023/02/23 13:10:08 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC2_H
# define VEC2_H

# define _USE_MATH_DEFINES
# include <math.h>

typedef float			t_v2f __attribute__((vector_size (8)));
typedef unsigned int	t_v2u __attribute__((vector_size (8)));
typedef int				t_v2i __attribute__((vector_size (8)));

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
