/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 09:38:43 by alde-fre          #+#    #+#             */
/*   Updated: 2022/11/25 09:38:44 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

void	ft_swap(void **a, void **b)
{
	void	*c;

	c = *a;
	*a = *b;
	*b = c;
}

float	ft_rand(float min, float max)
{
	return ((max - min) * ((float)rand() / (float)RAND_MAX) + min);
}
