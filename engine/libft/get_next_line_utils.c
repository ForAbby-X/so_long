/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:10:58 by motero            #+#    #+#             */
/*   Updated: 2022/11/25 06:30:58 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin1(char const *s1, char const *s2)
{
	char		*new_s;
	size_t		i;
	size_t		j;
	size_t		len_s1;
	size_t		len_s2;

	len_s1 = ft_strlen1(s1);
	len_s2 = ft_strlen1(s2);
	new_s = malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!new_s || !s1 || !s2)
		return (free(new_s), NULL);
	i = 0;
	while (i < len_s1)
	{
		new_s[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < len_s2)
	{
		new_s[i + j] = s2[j];
		j++;
	}
	new_s[i + j] = '\0';
	return (new_s);
}

size_t	ft_strlen1(const char *s)
{
	int	len;

	if (s == NULL)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}

int	ft_strchr_a(const char *s)
{
	char	*s_cpy;
	size_t	s_len;

	s_cpy = (char *)s;
	s_len = 0;
	while (s_cpy[s_len])
	{
		if (s_cpy[s_len++] == '\n')
			return ((--s_len));
	}
	return (-1);
}

void	ft_bzero1(void *s, size_t n)
{
	char	*ptr;
	size_t	i;

	ptr = (char *)s;
	i = 0;
	while (i < n)
		ptr[i++] = '\0';
}

void	*ft_calloc1(size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = (void *)malloc(nmemb * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero1(ptr, nmemb * size);
	return (ptr);
}
