/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:10:47 by motero            #+#    #+#             */
/*   Updated: 2022/12/02 17:20:28 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_free_nxtbuf(char *past_buf, char *next_buf)
{
	char	*temp;

	temp = ft_strjoin1(past_buf, next_buf);
	free(past_buf);
	return (temp);
}

char	*ft_free_line(char *save, int line_len)
{
	int		i;
	char	*next_buffer;

	if (!save[line_len])
	{
		free(save);
		return (NULL);
	}
	next_buffer = ft_calloc1(ft_strlen1(save + line_len) + 1, sizeof(char));
	line_len++;
	i = 0;
	while (save[line_len])
		next_buffer[i++] = save[line_len++];
	free(save);
	return (next_buffer);
}

char	*ft_extract_line(char *save, int line_len)
{
	char	*line;
	char	*buf;

	if (!save[0])
		return (NULL);
	line = ft_calloc1(line_len + 2, sizeof(char));
	if (!line)
		return (NULL);
	buf = line;
	while (line_len--)
		*buf++ = *save++;
	if (*save && *save == '\n')
		*buf++ = '\n';
	return (line);
}

//* 1- We calloc past_buf, only useful on the first use
// * 2- we initiliaze byte to 1, as we ensure to enter the main loop.
// * we read fd and save it to next_buf with BUF_SIZE and we verify that there 
// were no errors.
// * 3- We join the past_bufread with the next read
// * 4-  if a '\n' is found within te next buf, we interrupt the main loop 
// and we return the buf.*/

char	*ft_read_file(int fd, char *past_buf)
{
	static char	next_buf[BUFFER_SIZE + 1];
	int			byte;

	if (!past_buf)
		past_buf = ft_calloc1(1, 1);
	byte = 1;
	while (byte > 0)
	{
		byte = read(fd, next_buf, BUFFER_SIZE);
		if (byte == -1)
			return (NULL);
		next_buf[byte] = 0;
		if (byte == 0)
			break ;
		past_buf = ft_free_nxtbuf(past_buf, next_buf);
		if (ft_strchr_a(next_buf) != -1)
			break ;
	}
	return (past_buf);
}

///* 1- Verify if fd  is correct, buf_size is correct and read  is possible
// * 2- We use ft_read_file to read the file at least until there is a '\n', 
// insuring there is at least a line or EOF
// 3- we extract the first possible line or until EOF
// * 4-*/
char	*get_next_line(int fd)
{
	char		*line;
	static char	*save;
	int			line_len;

	if (fd < 0 || BUFFER_SIZE <= 0 || (read(fd, 0, 0) < 0))
	{
		free(save);
		save = NULL;
		return (NULL);
	}
	save = ft_read_file(fd, save);
	if (!save)
		return (NULL);
	line_len = 0;
	while (save[line_len] && save[line_len] != '\n')
		line_len++;
	line = ft_extract_line(save, line_len);
	save = ft_free_line(save, line_len);
	return (line);
}

/*#include <sys/stat.h>*/
/*#include <fcntl.h>*/

/*int main()*/
/*{*/
	/*int	fd;*/
	/*char *line;*/
	/*int	nbr_line;*/

	/*fd = open("big", O_RDONLY);*/
	/*if (fd < 0)*/
	/*{*/
		/*printf("Error opening the file\n");*/
		/*return (1);*/
	/*}*/
	/*nbr_line = 1;*/
	/*line = get_next_line(fd);*/
	/*while (nbr_line <= 2)*/
	/*{*/
		/*printf("|%i| %s", nbr_line++, line);*/
		/*line = get_next_line(fd);*/
	/*}*/
	/*printf("File is done");*/
	/*return 0;*/
/*}*/
