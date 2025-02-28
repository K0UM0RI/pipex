/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 22:55:32 by sbat              #+#    #+#             */
/*   Updated: 2025/02/03 22:55:33 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static size_t	countwords(const char *s, char c)
{
	size_t	l;

	l = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			l++;
		while (*s && *s != c)
			s++;
	}
	return (l);
}

static char	**freeing(char **c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		free(c[i]);
		i++;
	}
	free(c);
	return (NULL);
}

static void	wordlen(const char *s, char c, size_t *d, size_t *b)
{
	while (s[*b] == c && s[*b])
		*b = *b + 1;
	*d = *b;
	while (s[*b] != c && s[*b])
		*b = *b + 1;
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	size_t	count;
	size_t	j;
	size_t	d;
	size_t	b;

	if (!s)
		return (NULL);
	count = countwords(s, c);
	str = (char **)malloc(sizeof(char *) * (count + 1));
	if (!str)
		return (perror("ft_split malloc fail"), freeing(str, 0));
	j = 0;
	b = 0;
	while (j < count)
	{
		wordlen(s, c, &d, &b);
		str[j] = (char *)malloc(sizeof(char) * (b - d + 1));
		if (!str[j])
			return (perror("ft_split malloc fail"), freeing(str, j));
		ft_strlcpy(str[j++], s + d, b - d + 1);
	}
	str[count] = NULL;
	return (str);
}
