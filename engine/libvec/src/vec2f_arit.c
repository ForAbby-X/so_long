/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2f_arit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 07:59:25 by alde-fre          #+#    #+#             */
/*   Updated: 2022/12/23 18:46:53 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec2.h"

t_v2f	ft_v2f(float x, float y)
{
	t_v2f	a;

	a[0] = x;
	a[1] = y;
	return (a);
}

t_v2f	ft_v2fadd(t_v2f a, t_v2f b)
{
	return (ft_v2f(a[0] + b[0], a[1] + b[1]));
}

t_v2f	ft_v2fsub(t_v2f a, t_v2f b)
{
	return (ft_v2f(a[0] - b[0], a[1] - b[1]));
}

t_v2f	ft_v2fmul(t_v2f a, float n)
{
	return (ft_v2f(a[0] * n, a[1] * n));
}

t_v2f	ft_v2fdiv(t_v2f a, float n)
{
	return (ft_v2f(a[0] / n, a[1] / n));
}
