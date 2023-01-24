/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2i_arit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 07:59:20 by alde-fre          #+#    #+#             */
/*   Updated: 2022/12/23 18:46:53 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec2.h"

t_v2i	ft_v2i(int x, int y)
{
	t_v2i	a;

	a[0] = x;
	a[1] = y;
	return (a);
}

t_v2i	ft_v2iadd(t_v2i a, t_v2i b)
{
	return (ft_v2i(a[0] + b[0], a[1] + b[1]));
}

t_v2i	ft_v2isub(t_v2i a, t_v2i b)
{
	return (ft_v2i(a[0] - b[0], a[1] - b[1]));
}

t_v2i	ft_v2imul(t_v2i a, float n)
{
	return (ft_v2i(a[0] * n, a[1] * n));
}

t_v2i	ft_v2idiv(t_v2i a, float n)
{
	return (ft_v2i(a[0] / n, a[1] / n));
}
