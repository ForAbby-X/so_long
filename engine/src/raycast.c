/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 09:39:50 by alde-fre          #+#    #+#             */
/*   Updated: 2022/11/25 12:11:40 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	_ft_setup_ray(t_ray *ray, t_v2f start)
{
	if (ray->dir.x != 0.0f)
		ray->delta_dist.x = fabsf(1.0f / ray->dir.x);
	if (ray->dir.y != 0.0f)
		ray->delta_dist.y = fabsf(1.0f / ray->dir.y);
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (start.x - ray->pos.x) * ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->pos.x + 1.0f - start.x) * ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (start.y - ray->pos.y) * ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->pos.y + 1.0f - start.y) * ray->delta_dist.y;
	}
}

static	int	ft_ray_test(t_data *game, t_ray *ray, t_v2f end)
{
	return (ft_get_map(&game->map, ray->pos) == 0 && (ray->pos.x != floor(end.x)
			|| ray->pos.y != floor(end.y)) && (ray->pos.x >= 0
			&& ray->pos.x < game->map.size.x && ray->pos.y >= 0
			&& ray->pos.y < game->map.size.y));
}

int	ft_cast_ray(t_data *game, t_v2f start, t_v2f end)
{
	t_ray	ray;

	start = ft_v2fdiv(start, 32);
	end = ft_v2fdiv(end, 32);
	ray.dir = ft_v2fsub(end, start);
	if (ray.dir.x == 0.0f)
		ray.delta_dist.x = 1e30;
	if (ray.dir.y == 0.0f)
		ray.delta_dist.y = 1e30;
	ray.pos = (t_v2i){start.x, start.y};
	_ft_setup_ray(&ray, start);
	while (ft_ray_test(game, &ray, end))
	{
		if (ray.side_dist.x < ray.side_dist.y)
		{
			ray.side_dist.x += ray.delta_dist.x;
			ray.pos.x += ray.step.x;
		}
		else
		{
			ray.side_dist.y += ray.delta_dist.y;
			ray.pos.y += ray.step.y;
		}
	}
	return (ray.pos.x == floor(end.x) && ray.pos.y == floor(end.y));
}
