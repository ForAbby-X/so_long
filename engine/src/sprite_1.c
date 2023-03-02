/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 11:48:37 by alde-fre          #+#    #+#             */
/*   Updated: 2023/02/28 15:46:34 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

t_sprite	*ft_sprite(t_engine *eng, size_t dx, size_t dy)
{
	t_sprite	*spr;
	int			tab[3];

	spr = malloc(sizeof(t_sprite));
	if (spr == NULL)
		return (NULL);
	spr->img.image = mlx_new_image(eng->mlx, dx, dy);
	if (spr->img.image == NULL)
		return (free(spr), NULL);
	spr->img.data
		= mlx_get_data_addr(spr->img.image, &tab[0], &tab[1], &tab[2]);
	spr->data = (t_color *)(uint32_t *)spr->img.data;
	spr->size[0] = dx;
	spr->size[1] = dy;
	ft_putstr_fd("Created sprite [", 1);
	ft_putnbr_fd(spr->size[0], 1);
	ft_putstr_fd(":", 1);
	ft_putnbr_fd(spr->size[1], 1);
	ft_putstr_fd("]\n", 1);
	return (spr);
}

t_sprite	*ft_sprite_p(t_engine *eng, char *path)
{
	t_sprite	*spr;
	int			tab[3];
	int			xy[2];

	spr = malloc(sizeof(t_sprite));
	if (spr == NULL)
		return (NULL);
	spr->img.image = mlx_xpm_file_to_image(eng->mlx, path,
			&xy[0], &xy[1]);
	if (spr->img.image == NULL)
		return (free(spr), NULL);
	spr->size = (t_v2i){xy[0], xy[1]};
	spr->img.data
		= mlx_get_data_addr(spr->img.image, &tab[0], &tab[1], &tab[2]);
	spr->data = (t_color *)(uint32_t *)spr->img.data;
	ft_putstr_fd("Created sprite [", 1);
	ft_putnbr_fd(spr->size[0], 1);
	ft_putstr_fd(":", 1);
	ft_putnbr_fd(spr->size[1], 1);
	ft_putstr_fd("] - ", 1);
	ft_putstr_fd(path, 1);
	ft_putstr_fd("\n", 1);
	return (spr);
}

int	ft_destroy_sprite(t_engine *eng, t_sprite *spr)
{
	mlx_destroy_image(eng->mlx, spr->img.image);
	ft_putstr_fd("Destroyed sprite [", 1);
	ft_putnbr_fd(spr->size[0], 1);
	ft_putstr_fd(":", 1);
	ft_putnbr_fd(spr->size[1], 1);
	ft_putstr_fd("]\n", 1);
	free(spr);
	return (1);
}

t_sprite	*ft_cpy_sprite(t_engine *eng, t_sprite *spr)
{
	t_sprite	*res;

	if (spr == NULL)
		return (NULL);
	res = ft_sprite(eng, spr->size[0], spr->size[1]);
	if (res == NULL)
		return (NULL);
	ft_memcpy(res->data,
		spr->data, spr->size[0] * spr->size[1] * sizeof(t_color));
	return (res);
}
