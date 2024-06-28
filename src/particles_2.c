/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   particles_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 17:34:36 by alde-fre          #+#    #+#             */
/*   Updated: 2024/06/28 11:42:51 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	_ft_emmit_temp(t_data *game, t_v2f pos)
{
	t_particle	par;
	float		rot;

	rot = 0.0f;
	while (rot < M_PI * 2 * 3)
	{
		rot += ft_rand(M_PI / 4.0f, 1.75f);
		par.pos = pos;
		par.dir = ft_v2fr(rot, ft_rand(140, 185) * 6);
		par.accel = 0.0f;
		par.time = 0.0f;
		par.life_time = (185.0f - ft_v2fmag(par.dir)) / 1000.0f;
		par.spr = game->spr[39];
		par.off = (t_v2i){3, 3};
		vector_addback(&game->map->particles, &par);
	}
}

void	ft_emmit_explosion(t_data *game, t_v2f pos, float force)
{
	t_particle	par;
	int			nb;

	nb = force * (force / 6.0f);
	while (nb)
	{
		nb--;
		par.pos = pos;
		par.dir = ft_v2fr(ft_rand(-M_PI, M_PI), ft_rand(0, force * 2 * 4));
		par.accel = 0.0f;
		par.time = 0.0f;
		par.life_time = 0.4f - ft_v2fmag(par.dir) / (force * 2 * 4) * 0.2f;
		par.spr = game->spr[22 + ((rand() & 3) == 0) * 30];
		par.off = (t_v2i){3, 3};
		vector_addback(&game->map->particles, &par);
	}
	_ft_emmit_temp(game, pos);
}

void	ft_emmit_flame_pipe(t_data *game, t_length nb, t_v2f pos)
{
	t_particle	par;

	while (nb)
	{
		nb--;
		par.pos = pos;
		par.dir = ft_v2fr(ft_rand(-M_PI_2 - 0.2, -M_PI_2 + 0.2),
				ft_rand(40, 60));
		par.accel = 0.0f;
		par.time = 0.0f;
		par.life_time = ft_rand(1.0f, 1.3f);
		par.spr = game->spr[52];
		par.off = (t_v2i){1, 2};
		vector_addback(&game->map->particles, &par);
	}
}

void	ft_emmit_gear(t_data *game, t_v2f pos, int nb)
{
	t_particle	par;

	while (nb)
	{
		nb--;
		par.pos = pos + (t_v2f){ft_rand(-16.f, 16.f), ft_rand(-16.f, 16.f)};
		par.dir = (t_v2f){0.0f, ft_rand(-15.0f, -10.0f)};
		par.accel = 0.0f;
		par.time = 0.0f;
		par.life_time = ft_rand(1.0f, 1.3f);
		par.spr = game->spr[56];
		par.off = (t_v2i){9, 9};
		vector_addback(&game->map->particles, &par);
	}
}
