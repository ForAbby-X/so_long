/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 09:29:30 by alde-fre          #+#    #+#             */
/*   Updated: 2023/02/11 11:53:26 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static	int	ft_eng_loop(t_engine *eng)
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

static	void	_ft_unzip_ascii(t_color *address)
{
	uint32_t			u[3];
	static char const	tab[]
		= "gF^cagfooooolMaST40ASooooS68HQ02;P0LmcXQR607>Li`<oW_mo_oknO_gikooooo"
		"ogoooook^ome[0cMkf[OooljKWENocWKggmg>LicW_LkOW?8icW>O]cW>MkKmeo_konoOk"
		"ooNoooooomooooomkgoO`;j_mnagoon\\GkcG_jigok1]b7>Nikg^gi[e6LicWkLieJmgO"
		"OooR6<8PP4N6_:68H9P5cW>L3Nmfgn\\MgoOX0O1oJ]mb08MaQomomjX0G^25h=n6mbW1L"
		"6>g>M_Nmkgooo>Lieg>ghKe>LiaWgLieGM__ZMo1Zj_gk7Noo^KNoMljk_Og\\6mXLikW_"
		"HkOV_Lace>m]cUEgOOMoon3W^1N3]nJmCW1Pn=g>M^6mkgoojQHgnmZg_og^gMgO>^kfmm"
		"oOkg>Likg>ficg>Lm[_KMDS]_gkOooLicWglkKW?Lico?mIeEEmONmogn^nBofoogo_l@0"
		"Sd<KaSnooog5`HQ0n;PAL1cX_Th>hkLkH<oWl7h1S25h^15dG>Roc`iQ^[XPk^o`oo";

	u[0] = 0;
	while (u[0] < 549)
	{
		u[1] = (tab[u[0] + 0] - '0') << 18 | (tab[u[0] + 1] - '0') << 12
			| (tab[u[0] + 2] - '0') << 6 | (tab[u[0] + 3] - '0');
		u[2] = -1;
		while (++u[2] < 24)
		{
			address[u[0] * 6 + u[2]] = ft_color(0, 255, 255, 255);
			if (u[1] & (1 << (23 - u[2])))
				address[u[0] * 6 + u[2]] = ft_color(255, 0, 0, 0);
		}
		u[0] += 4;
	}
}

static	int	_ft_eng_create_2(t_engine *eng)
{
	ft_setup_hooks(eng);
	eng->sel_spr = eng->screen;
	eng->on_repeat = NULL;
	eng->ascii_spr = ft_sprite(eng, 470, 7);
	if (eng->ascii_spr == NULL)
		return (ft_putstr_fd("ERROR: couldn't create ASCII textures.", 2), 0);
	_ft_unzip_ascii(eng->ascii_spr->data);
	return (1);
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
	eng->win_x = size_x;
	eng->win_y = size_y;
	if (_ft_eng_create_2(eng) == 0)
		return (ft_destroy_sprite(eng, eng->screen), mlx_destroy_window(
				eng->mlx, eng->win), free(eng->mlx), free(eng), NULL);
	return (eng);
}
