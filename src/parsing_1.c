/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:38:41 by alde-fre          #+#    #+#             */
/*   Updated: 2023/01/24 15:28:16 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static int	_ft_pars_error(t_vector *lines, char *error)
{
	t_length	i;

	if (error)
	{
		ft_putstr_fd("Error:", 2);
		ft_putendl_fd(error, 2);
	}
	i = 0;
	while (lines && i < ft_vector_size(lines))
		free(ft_vector_get(lines, i++));
	if (lines)
		ft_vector_destroy(lines);
	return (0);
}

static t_vector	*_ft_read_file(int fd, t_v2i *size, char **name)
{
	t_vector	*lines;
	char		*line;

	lines = ft_vector_create(16);
	if (lines == NULL)
		return (NULL);
	line = get_next_line(fd);
	while (line)
	{
		if (ft_vector_add(lines, line) == NULL)
			return (get_next_line(-1),
				_ft_pars_error(lines, "Failed to read line"), NULL);
		line = get_next_line(fd);
	}
	get_next_line(-1);
	if (ft_vector_size(lines) < 5)
		return (_ft_pars_error(lines, "Map is too high"), NULL);
	*name = ft_strdup(ft_vector_get(lines, 0));
	(*name)[ft_strlen(*name) - 1] = 0;
	line = ft_vector_get(lines, 1);
	(*size)[0] = ft_strchr(line, '\n') - line;
	(*size)[1] = (int)ft_vector_size(lines) - 1;
	if ((*size)[0] < 4)
		return (free(*name), _ft_pars_error(lines, "Map is too thin"), NULL);
	return (lines);
}

static int	_ft_pars_str(int fd, char **data, t_v2i *size, char **name)
{
	t_vector	*lines;
	char		*line;
	t_length	i;

	lines = _ft_read_file(fd, size, name);
	if (lines == NULL)
		return (_ft_pars_error(lines, "Failed to read file"));
	*data = malloc((*size)[0] * (*size)[1] * sizeof(char));
	if (*data == NULL)
		return (_ft_pars_error(lines, "Failed to allocate memory"));
	i = 1;
	while (i < ft_vector_size(lines))
	{
		line = ft_vector_get(lines, i);
		if (ft_strchr(line, '\n') - line != (*size)[0])
			return (free(*name), free(*data),
				_ft_pars_error(lines, "Map is not a rect"));
		ft_memcpy(*data + (i - 1) * (*size)[0], line, (*size)[0]);
		i++;
	}
	_ft_pars_error(lines, NULL);
	return (1);
}

t_vector	*ft_pars_folder(t_data *game)
{
	DIR				*folder;
	struct dirent	*entry;
	t_vector		*map_vector;
	t_map			*map;

	folder = opendir("maps");
	if (folder == NULL)
		return (NULL);
	map_vector = ft_vector_create(1);
	if (map_vector == NULL)
		return (closedir(folder), NULL);
	entry = readdir(folder);
	while (entry)
	{
		if (ft_strncmp(ft_strrchr(entry->d_name, '.'), ".ber", 4) == 0)
		{
			map = ft_pars_file(game, entry->d_name);
			if (map)
				ft_vector_add(map_vector, map);
		}
		entry = readdir(folder);
	}
	closedir(folder);
	return (map_vector);
}

t_map	*ft_pars_file(t_data *game, char *str)
{
	int		fd;
	t_map	*map;
	char	*data;
	t_v2i	size;
	char	*name;

	ft_putstr_fd("Parsing: ", 1);
	ft_putendl_fd(str, 1);
	ft_memmove(str + 5, str, ft_strlen(str) + 1);
	ft_memcpy(str, "maps/", 5);
	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd("Failed to open file", 2), NULL);
	data = NULL;
	size = (t_v2i){0, 0};
	name = NULL;
	if (_ft_pars_str(fd, &data, &size, &name) == 0)
		return (ft_putstr_fd("Couldn't parse file\n", 2), close(fd), NULL);
	map = ft_map_create(game, data, size, name);
	if (map == NULL)
		return (ft_putstr_fd("Failed to create map\n", 2), close(fd), NULL);
	if (ft_check_map(map) == 0)
		return (ft_map_destroy(game, map), NULL);
	close(fd);
	return (ft_putstr_fd("Success\n", 2), map);
}
