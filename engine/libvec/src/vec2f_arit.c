/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2f_arit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 07:59:25 by alde-fre          #+#    #+#             */
/*   Updated: 2022/11/25 07:59:26 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec2.h"

t_v2f	ft_v2f(float x, float y)
{
	t_v2f	a;

	a.x = x;
	a.y = y;
	return (a);
}

t_v2f	ft_v2fadd(t_v2f a, t_v2f b)
{
	return (ft_v2f(a.x + b.x, a.y + b.y));
}

t_v2f	ft_v2fsub(t_v2f a, t_v2f b)
{
	return (ft_v2f(a.x - b.x, a.y - b.y));
}

t_v2f	ft_v2fmul(t_v2f a, float n)
{
	return (ft_v2f(a.x * n, a.y * n));
}

t_v2f	ft_v2fdiv(t_v2f a, float n)
{
	return (ft_v2f(a.x / n, a.y / n));
}
