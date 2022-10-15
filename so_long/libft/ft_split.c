/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 20:19:06 by alde-fre          #+#    #+#             */
/*   Updated: 2022/09/21 20:19:09 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_free(char **tab, int size)
{
	while (size >= 0)
	{
		free(tab[size]);
		size--;
	}
	free(tab);
	tab = 0;
}

static int	ft_len_word(const char *s, char c)
{
	int	i;
	int	j;
	int	nb_words;

	i = 0;
	nb_words = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		j = 0;
		while (s[i + j] && s[i + j] != c)
			j++;
		if (j)
			nb_words++;
		i += j;
	}
	return (nb_words);
}

static void	ft_balec(char **tab, const char *s, char c, int nb_words)
{
	int	i;
	int	j;
	int	word_len;

	i = 0;
	j = 0;
	tab[nb_words] = 0;
	while (i < nb_words)
	{
		while (s[j] && s[j] == c)
			j++;
		word_len = 0;
		while (s[j + word_len] && s[j + word_len] != c)
			word_len++;
		tab[i] = ft_substr(s, j, word_len);
		if (!tab[i])
		{
			ft_free(tab, nb_words);
			break ;
		}
		j += word_len;
		i++;
	}
}

char	**ft_split(const char *s, char c)
{
	int		nb_words;
	char	**tab;

	if (!s)
		return (NULL);
	nb_words = ft_len_word(s, c);
	tab = malloc(sizeof(char *) * (nb_words + 1));
	if (!tab)
		return (NULL);
	ft_balec(tab, s, c, nb_words);
	return (tab);
}
