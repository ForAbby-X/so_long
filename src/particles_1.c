/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   particles_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 06:02:48 by alde-fre          #+#    #+#             */
/*   Updated: 2023/02/12 17:34:33 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	ft_emmit_sparks(t_data *game, t_length nb, t_v2f pos, float rot)
{
	t_particle	*par;

	while (nb)
	{
		par = malloc(sizeof(t_particle));
		nb--;
		if (par == NULL)
			continue ;
		par->pos = pos;
		par->dir = ft_v2fr(rot + ft_rand(-1.5, 1.5), ft_rand(180, 220));
		par->accel = 0;
		par->time = 0;
		par->life_time = 0.125f;
		par->spr = game->spr[20];
		par->off = (t_v2i){1, 1};
		ft_vector_add(game->map->particles, par);
	}
}

void	ft_emmit_blood(t_data *game, t_length nb, t_v2f pos, float rot)
{
	t_particle	*par;

	while (nb)
	{
		par = malloc(sizeof(t_particle));
		nb--;
		if (par == NULL)
			continue ;
		par->pos = pos;
		par->dir = ft_v2fr(rot + ft_rand(-0.8, 0.8), ft_rand(80, 140));
		par->accel = 0;
		par->time = 0;
		par->life_time = ft_rand(0.25f, 0.35f);
		par->spr = game->spr[21];
		par->off = (t_v2i){2, 2};
		ft_vector_add(game->map->particles, par);
	}
}

void	ft_emmit_pool_blood(t_data *game, t_length nb, t_v2f pos)
{
	t_particle	*par;

	while (nb)
	{
		par = malloc(sizeof(t_particle));
		nb--;
		if (par == NULL)
			continue ;
		par->pos = pos;
		par->dir = ft_v2fr(ft_rand(-M_PI, M_PI), ft_rand(20, 40));
		par->accel = 0.0f;
		par->time = 0.0f;
		par->life_time = ft_rand(0.35f, 0.45f);
		par->spr = game->spr[21];
		par->off = (t_v2i){2, 2};
		ft_vector_add(game->map->particles, par);
	}
}

void	ft_emmit_smoke_pipe(t_data *game, t_length nb, t_v2f pos)
{
	t_particle	*par;

	while (nb)
	{
		par = malloc(sizeof(t_particle));
		nb--;
		if (par == NULL)
			continue ;
		par->pos = pos;
		par->dir = ft_v2fr(ft_rand(-M_PI_2 - 0.4, -M_PI_2 + 0.4),
				ft_rand(40, 60));
		par->accel = 0.0f;
		par->time = 0.0f;
		par->life_time = ft_rand(1.0f, 1.3f);
		par->spr = game->spr[22];
		par->off = (t_v2i){3, 3};
		ft_vector_add(game->map->particles, par);
	}
}

void	ft_emmit_wood(t_data *game, t_v2f pos)
{
	t_particle	*par;
	int			nb;

	nb = 20;
	while (nb)
	{
		par = malloc(sizeof(t_particle));
		nb--;
		if (par == NULL)
			continue ;
		par->pos = pos;
		par->dir = ft_v2fr(ft_rand(-M_PI, M_PI), ft_rand(35, 95));
		par->accel = 0.0f;
		par->time = 0.0f;
		par->life_time = ft_rand(0.25f, 0.45f);
		par->spr = game->spr[35];
		par->off = (t_v2i){2, 2};
		ft_vector_add(game->map->particles, par);
	}
}
