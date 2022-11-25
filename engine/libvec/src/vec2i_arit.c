/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2i_arit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 07:59:20 by alde-fre          #+#    #+#             */
/*   Updated: 2022/11/25 07:59:22 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
