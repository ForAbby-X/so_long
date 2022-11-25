/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 10:55:22 by alde-fre          #+#    #+#             */
/*   Updated: 2022/11/25 09:39:00 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

/* NEED TO ADD ELAPSED TIME CALCULATION */
static int	ft_eng_loop(t_engine *eng)
{
	int		flag;
	double	time_m;

	clock_gettime(CLOCK_MONOTONIC, &eng->time_s);
	time_m = (double)(eng->time_s.tv_sec - eng->time_e.tv_sec)
		+ ((double)(eng->time_s.tv_nsec - eng->time_e.tv_nsec)) * 1e-9;
	flag = eng->on_repeat(eng, eng->data, time_m);
	mlx_put_image_to_window(eng->mlx, eng->win, eng->screen->img.image, 0, 0);
	eng->time_e = eng->time_s;
	if (flag == 0 || eng->keys[XK_Escape])
		ft_eng_close(eng);
	return (flag);
}

static	void	ft_setup_hooks(t_engine *eng)
{
	mlx_hook(eng->win, 2, (1L << 0), (&ft_eng_pressed_keys), eng);
	mlx_hook(eng->win, 3, (1L << 1), (&ft_eng_released_keys), eng);
	mlx_hook(eng->win, 4, (1L << 2), (&ft_eng_pressed_mouse), eng);
	mlx_hook(eng->win, 5, (1L << 3), (&ft_eng_released_mouse), eng);
	mlx_hook(eng->win, 6, (1L << 6), (&ft_eng_moved_mouse), eng);
	mlx_hook(eng->win, 17, (0L), (&ft_eng_close), eng);
	mlx_loop_hook(eng->mlx, (&ft_eng_loop), eng);
}

t_engine	*ft_eng_create(size_t size_x, size_t size_y, char *title)
{
	t_engine	*eng;

	ft_putstr_fd("Creating engine...\n", 1);
	eng = malloc(sizeof(t_engine));
	if (eng == NULL)
		return (NULL);
	ft_memset(eng, 0, sizeof(t_engine));
	eng->mlx = mlx_init();
	if (eng->mlx == NULL)
		return (free(eng), NULL);
	eng->win = mlx_new_window(eng->mlx, size_x, size_y, title);
	if (eng->win == NULL)
		return (free(eng->mlx), free(eng), NULL);
	eng->screen = ft_sprite(eng, size_x, size_y);
	if (eng->screen == NULL)
		return (mlx_destroy_window(eng->mlx, eng->win),
			free(eng->mlx), free(eng), NULL);
	ft_setup_hooks(eng);
	eng->sel_spr = eng->screen;
	eng->win_x = size_x;
	eng->win_y = size_y;
	eng->on_repeat = NULL;
	return (eng);
}

void	ft_eng_destroy(t_engine *eng)
{
	mlx_loop_end(eng->mlx);
	ft_destroy_sprite(eng, eng->screen);
	mlx_destroy_window(eng->mlx, eng->win);
	mlx_destroy_display(eng->mlx);
	free(eng->mlx);
	free(eng);
	ft_putstr_fd("Destroying engine...\n", 1);
}

int	ft_eng_play(t_engine *eng, t_data *data,
		int (*on_repeat)(t_engine *eng, t_data *data, double elapsed_time))
{
	ft_putstr_fd("Starting engine...\n", 1);
	if (on_repeat)
	{
		eng->data = data;
		eng->on_repeat = on_repeat;
		clock_gettime(CLOCK_MONOTONIC, &eng->time_e);
		mlx_loop(eng->mlx);
	}
	return (1);
}
