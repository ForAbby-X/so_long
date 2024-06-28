/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [2]parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 16:38:02 by alde-fre          #+#    #+#             */
/*   Updated: 2024/06/28 12:03:01 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static int	_ft_check_flood(char *data, t_v2i size, t_v2i start, t_length *flag)
{
	int	ret;

	if (start[0] < 0 || start[0] >= size[0]
		|| start[1] < 0 || start[1] >= size[1]
		|| data[start[0] + start[1] * size[0]] == '1'
		|| data[start[0] + start[1] * size[0]] == '*')
		return (0);
	ret = (data[start[0] + start[1] * size[0]] == 'C');
	if (data[start[0] + start[1] * size[0]] == 'E')
		*flag = 1;
	data[start[0] + start[1] * size[0]] = '*';
	ret += _ft_check_flood(data, size, (t_v2i){start[0] + 1, start[1]}, flag);
	ret += _ft_check_flood(data, size, (t_v2i){start[0] - 1, start[1]}, flag);
	ret += _ft_check_flood(data, size, (t_v2i){start[0], start[1] + 1}, flag);
	ret += _ft_check_flood(data, size, (t_v2i){start[0], start[1] - 1}, flag);
	return (ret);
}

static int	_ft_check_result(t_map *map, t_length start,
	t_length exit, int coins)
{
	int		i;
	char	*dat;

	if (exit > 1)
		return (ft_putstr_fd("ERROR: More than one exit.\n", 2), 0);
	if (exit == 0)
		return (ft_putstr_fd("ERROR: No exit point.\n", 2), 0);
	if (start > 1)
		return (ft_putstr_fd("ERROR: More than one player spawn.\n", 2), 0);
	if (start == 0)
		return (ft_putstr_fd("ERROR: No player spawn.\n", 2), 0);
	if (coins == 0)
		return (ft_putstr_fd("ERROR: No coins on map.\n", 2), 0);
	i = -1;
	while (map->data[++i] != 'P')
		exit = 0;
	dat = malloc(map->size[0] * map->size[1] * sizeof(char));
	if (dat == NULL)
		return (ft_putstr_fd("ERROR: Failed to allocate memory.\n", 2), 0);
	ft_memcpy(dat, map->data, map->size[0] * map->size[1] * sizeof(char));
	if (_ft_check_flood(dat, map->size, (t_v2i){i % map->size[0],
			i / map->size[0]}, &exit) < coins || exit == 0)
		return (ft_putstr_fd("ERROR: There is no correct path.\n", 2),
			free(dat), 0);
	return (free(dat), 1);
}

int	ft_check_map(t_map *map)
{
	int			i;
	t_length	val[3];

	i = 0;
	val[0] = 0;
	val[1] = 0;
	val[2] = 0;
	while (i < map->size[0] * map->size[1])
	{
		if (ft_strchr("01CEP", map->data[i]) == NULL)
			return (ft_putstr_fd("ERROR: unknown character.\n", 2), 0);
		if (map->data[i] != '1' && ((i / map->size[0]) == 0
				|| (i / map->size[0]) == map->size[1] - 1
				|| (i % map->size[0]) == 0
				|| (i % map->size[0]) == map->size[0] - 1))
			return (ft_putstr_fd("ERROR: map isn't closed.\n", 2), 0);
		if (map->data[i] == 'P')
			val[0]++;
		if (map->data[i] == 'E')
			val[1]++;
		if (map->data[i] == 'C')
			val[2]++;
		i++;
	}
	return (_ft_check_result(map, val[0], val[1], val[2]));
}
