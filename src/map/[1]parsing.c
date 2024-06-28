/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [1]parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:38:41 by alde-fre          #+#    #+#             */
/*   Updated: 2024/06/28 13:39:40 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static int	_ft_pars_error(t_vector *lines, char *error)
{
	t_object	ret;

	if (error)
	{
		ft_putstr_fd("Error:", 2);
		ft_putendl_fd(error, 2);
	}
	if (lines)
	{
		while (vector_size(lines))
		{
			ret = vector_pop(lines);
			if (ret)
				free(*((char**)ret));
		}
		vector_destroy(lines);
	}
	return (0);
}

static t_vector	_ft_read_file(int fd, t_v2i *size, char **name)
{
	t_vector	lines;
	char		*line;

	lines = vector_create(sizeof(char *));
	if (lines.data == NULL)
		return ((t_vector){0});
	line = get_next_line(fd);
	*name = NULL;
	while (line)
	{
		if (vector_addback(&lines, &line) == NULL)
			return (get_next_line(-1),
				_ft_pars_error(&lines, "Failed to read line"), (t_vector){0});
		line = get_next_line(fd);
	}
	get_next_line(-1);
	if (vector_size(&lines) < 4)
		return (_ft_pars_error(&lines, "Map is not high enough"), (t_vector){0});
	*name = ft_strdup(*(char **)vector_get(&lines, 0));
	line = *(char**)vector_get(&lines, 1);
	(*size) = (t_v2i){ft_strchr(line, '\n') - line, vector_size(&lines) - 1u};
	if ((*size)[0] * (*size)[1] < 15)
		return (_ft_pars_error(&lines, "Map is too small"), (t_vector){0});
	return (lines);
}

static int	_ft_pars_str(int fd, char **data, t_v2i *size, char **name)
{
	t_vector	lines;
	char		*line;
	t_length	i;

	lines = _ft_read_file(fd, size, name);
	if (*name == NULL)
		return (_ft_pars_error(&lines, "Failed to allocate name"));
	(*name)[ft_strlen(*name) - 1] = 0;
	if (lines.data == NULL)
		return (free(*name), _ft_pars_error(&lines, "Failed to read file"));
	*data = malloc((*size)[0] * (*size)[1] * sizeof(char));
	if (*data == NULL)
		return (free(*name), _ft_pars_error(&lines, "Failed to allocate space"));
	i = 1;
	while (i < vector_size(&lines))
	{
		line = *((char **)vector_get(&lines, i));
		if (ft_strchr(line, '\n') - line != (*size)[0])
			return (free(*name), free(*data),
				_ft_pars_error(&lines, "Map is not a rect"));
		ft_memcpy(*data + (i - 1) * (*size)[0], line, (*size)[0]);
		i++;
	}
	_ft_pars_error(&lines, NULL);
	return (1);
}

t_vector	ft_pars_folder(t_data *game)
{
	DIR				*folder;
	struct dirent	*entry;
	t_vector		map_vector;
	t_map			map;

	folder = opendir("maps");
	if (folder == NULL)
		return ((t_vector){0});
	map_vector = vector_create(sizeof(t_map));
	if (map_vector.data == NULL)
		return (closedir(folder), (t_vector){0});
	entry = readdir(folder);
	while (entry && map_vector.size < 10)
	{
		if (ft_strncmp(ft_strrchr(entry->d_name, '.'), ".ber", 5) == 0)
		{
			map = ft_pars_file(game, entry->d_name);
			if (map.data != NULL)
				if (vector_addback(&map_vector, &map) == NULL)
					return (ft_map_destroy(game, &map), (t_vector){0});
		}
		entry = readdir(folder);
	}
	closedir(folder);
	return (map_vector);
}

t_map	ft_pars_file(t_data *game, char *str)
{
	int		fd;
	t_map	map;
	char	*data;
	t_v2i	size;
	char	*name;

	ft_putstr_fd("[Parsing] ", 1);
	ft_putendl_fd(str, 1);
	ft_memcpy(ft_memmove(str + 5, str, ft_strlen(str) + 1) - 5, "maps/", 5);
	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd("Failed to open file\n", 2), (t_map){0});
	size = (t_v2i){0, 0};
	name = NULL;
	if (_ft_pars_str(fd, &data, &size, &name) == 0)
		return (ft_putstr_fd("Couldn't parse file\n", 2), close(fd), (t_map){0});
	if (size[0] * size[1] > 74000)
		return (ft_putstr_fd("Map too big\n", 2),
			free(data), free(name), close(fd), (t_map){0});
	map = ft_map_create(game, data, size, name);
	if (map.data == NULL)
		return (ft_putstr_fd("Failed to create map\n", 2), close(fd), (t_map){0});
	if (ft_check_map(&map) == 0)
		return (ft_map_destroy(game, &map), close(fd), (t_map){0});
	return (ft_putstr_fd("[Parsing] success\n", 1), close(fd), map);
}
