/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 09:39:50 by alde-fre          #+#    #+#             */
/*   Updated: 2023/02/15 14:13:54 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	_ft_setup_ray(t_ray *ray, t_v2f st)
{
	if (ray->dir[0] != 0.0f)
		ray->delta_dist[0] = fabsf(1.0f / ray->dir[0]);
	if (ray->dir[1] != 0.0f)
		ray->delta_dist[1] = fabsf(1.0f / ray->dir[1]);
	if (ray->dir[0] < 0)
	{
		ray->step[0] = -1;
		ray->side_dist[0] = (st[0] - ray->pos[0]) * ray->delta_dist[0];
	}
	else
	{
		ray->step[0] = 1;
		ray->side_dist[0] = (ray->pos[0] + 1.0f - st[0]) * ray->delta_dist[0];
	}
	if (ray->dir[1] < 0)
	{
		ray->step[1] = -1;
		ray->side_dist[1] = (st[1] - ray->pos[1]) * ray->delta_dist[1];
	}
	else
	{
		ray->step[1] = 1;
		ray->side_dist[1] = (ray->pos[1] + 1.0f - st[1]) * ray->delta_dist[1];
	}
}

static	int	ft_ray_test(t_data *game, t_ray *ray, t_v2f end)
{
	return (ft_get_map(game->map, ray->pos) != '1'
		&& (ray->pos[0] != floor(end[0])
			|| ray->pos[1] != floor(end[1])) && (ray->pos[0] >= 0
			&& ray->pos[0] < game->map->size[0] && ray->pos[1] >= 0
			&& ray->pos[1] < game->map->size[1]));
}

int	ft_cast_ray(t_data *game, t_v2f start, t_v2f end)
{
	t_ray	ray;

	start = start / 32;
	end = end / 32;
	ray.dir = end - start;
	if (ray.dir[0] == 0.0f)
		ray.delta_dist[0] = 1e30;
	if (ray.dir[1] == 0.0f)
		ray.delta_dist[1] = 1e30;
	ray.pos = (t_v2i){start[0], start[1]};
	_ft_setup_ray(&ray, start);
	while (ft_ray_test(game, &ray, end))
	{
		if (ray.side_dist[0] < ray.side_dist[1])
		{
			ray.side_dist[0] += ray.delta_dist[0];
			ray.pos[0] += ray.step[0];
		}
		else
		{
			ray.side_dist[1] += ray.delta_dist[1];
			ray.pos[1] += ray.step[1];
		}
	}
	return (ray.pos[0] == floor(end[0]) && ray.pos[1] == floor(end[1]));
}
