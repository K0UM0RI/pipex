/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 22:55:54 by sbat              #+#    #+#             */
/*   Updated: 2025/02/03 22:56:50 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

size_t	ft_strlen(const char *s)
{
	size_t	n;

	if (!s)
		return (0);
	n = 0;
	while (s[n])
		n++;
	return (n);
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

char	*ft_strdup(const char *s)
{
	char	*c;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	c = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!c)
		return (perror("ft_strdup malloc fail"), NULL);
	while (s[i])
	{
		c[i] = s[i];
		i++;
	}
	c[i] = '\0';
	return (c);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	slen;

	if (!src)
		return (0);
	slen = ft_strlen(src);
	i = 0;
	if (dstsize == 0 || !dst)
		return (slen);
	while (i + 1 < dstsize && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (slen);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	dl;
	size_t	sl;

	if (!src)
		return (size);
	sl = ft_strlen(src);
	if (!dst)
		return (sl);
	dl = ft_strlen(dst);
	j = 0;
	i = dl;
	if (i >= size)
		return (sl + size);
	while (src[j] && i < size - 1)
	{
		dst[i] = src[j];
		j++;
		i++;
	}
	dst[i] = '\0';
	return (dl + sl);
}
