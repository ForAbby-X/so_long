/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2f_algo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 07:59:28 by alde-fre          #+#    #+#             */
/*   Updated: 2023/01/29 13:23:45 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec2.h"

t_v2f	ft_v2fr(float r, float d)
{
	return ((t_v2f){cosf(r), sinf(r)} * d);
}

float	ft_v2fmag(t_v2f a)
{
	a *= a;
	return (sqrtf(a[0] + a[1]));
}

float	ft_v2fdot(t_v2f a, t_v2f b)
{
	a *= b;
	return (a[0] + a[1]);
}

float	ft_v2fcross(t_v2f a, t_v2f b)
{
	return (a[0] * b[1] - a[1] * b[0]);
}

t_v2f	ft_v2fnorm(t_v2f a, float n)
{
	float	mag;

	mag = ft_v2fmag(a);
	if (mag == 0.0f)
		return ((t_v2f){0.0f, 0.0f});
	return (a / mag * n);
}
