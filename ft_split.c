/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:57:01 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/01/18 18:12:55 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	substr_count(char const *s, int c)
{
	size_t	count;
	size_t	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static char	*fill_substr(const char *src, size_t len)
{
	char	*dest;

	if (!src)
		return (NULL);
	dest = (char *)malloc(sizeof(char) * len);
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, src, len);
	return (dest);
}

static char	**ft_free(char **strs, int count)
{
	while (--count >= 0)
		free(*(strs + count));
	free(strs);
	return (NULL);
}

static int	iterate_i(const char *s, int i, char c)
{
	while (*(s + i) && *(s + i) != c)
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**split_strs;
	int		i;
	int		j;
	int		i_word;

	split_strs = (char **)malloc((substr_count(s, c) + 1) * sizeof(char *));
	if (!split_strs || !s)
		return (NULL);
	j = 0;
	i = 0;
	while (*(s + i))
	{
		if (*(s + i) == c)
			i++;
		i_word = i;
		i = iterate_i(s, i, c);
		if (i_word < i)
		{
			*(split_strs + j++) = fill_substr(&s[i_word], (i - i_word) + 1);
			if (!(*(split_strs + j - 1)))
				return (ft_free(split_strs, j));
		}
	}
	*(split_strs + j) = NULL;
	return (split_strs);
}
