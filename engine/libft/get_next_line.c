/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 17:37:38 by alde-fre          #+#    #+#             */
/*   Updated: 2023/02/03 14:55:44 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_endln(char const *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

static char	*ft_readline(int fd, char **line)
{
	char	*buff;
	ssize_t	count;

	buff = malloc(BUFFER_SIZE + 1);
	if (buff == NULL)
		return (free(*line), *line = NULL, NULL);
	buff[0] = '\0';
	count = read(fd, buff, BUFFER_SIZE);
	while (count > 0)
	{
		buff[count] = '\0';
		*line = ft_strjoin2(*line, buff);
		if (*line == NULL || ft_is_end(buff))
			break ;
		count = read(fd, buff, BUFFER_SIZE);
	}
	free(buff);
	return (*line);
}

static char	*ft_getline(char *str)
{
	char	*line;
	size_t	end;
	size_t	i;

	end = ft_endln(str);
	if (str[end] == '\n')
		end++;
	line = malloc(end + 1);
	if (line == NULL)
		return (NULL);
	i = 0;
	while (i < end)
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*ft_cropline(char **str)
{
	char	*line;
	size_t	size;
	size_t	end;
	size_t	i;

	end = ft_endln(*str);
	if ((*str)[end] == '\n')
		end++;
	size = ft_strlen2(*str) - end;
	if (size <= 0)
		return (free(*str), *str = NULL, NULL);
	line = malloc(size + 1);
	if (line == NULL)
		return (free(*str), *str = NULL, NULL);
	i = 0;
	while (i < size)
	{
		line[i] = (*str)[end + i];
		i++;
	}
	line[i] = '\0';
	free(*str);
	*str = NULL;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*last_ln = NULL;
	char		*line;

	if (BUFFER_SIZE < 1 || (fd < 0 && last_ln == NULL))
		return (NULL);
	if (fd < 0 && last_ln)
		return (free(last_ln), last_ln = NULL, NULL);
	if (!ft_is_end(last_ln))
		last_ln = ft_readline(fd, &last_ln);
	if (last_ln == NULL)
		return (NULL);
	line = ft_getline(last_ln);
	last_ln = ft_cropline(&last_ln);
	return (line);
}
