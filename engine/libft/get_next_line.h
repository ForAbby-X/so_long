/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:12:27 by motero            #+#    #+#             */
/*   Updated: 2022/11/25 02:56:48 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char	*ft_strjoin1(char const *s1, char const *s2);
size_t	ft_strlen1(const char *s);
int		ft_strchr_a(const char *s);
void	ft_bzero1(void *s, size_t n);
void	*ft_calloc1(size_t nmemb, size_t size);
char	*ft_free_line(char *save, int line_len);
char	*ft_extract_line(char *save, int line_len);
char	*ft_read_file(int fd, char *past_buf);
char	*get_next_line(int fd);
char	*ft_free_nxtbuf(char *past_buf, char *next_buf);

#endif
