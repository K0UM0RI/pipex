/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 22:55:47 by sbat              #+#    #+#             */
/*   Updated: 2025/02/03 22:56:24 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*c;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	c = malloc((len1 + len2 + 1) * sizeof(char));
	if (!c)
		return (perror("ft_strjoin malloc fail"), NULL);
	ft_strlcpy(c, s1, len1 + 1);
	ft_strlcat(c + len1, s2, len1 + len2 + 1);
	return (c);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (i < n)
	{
		if (s1[i] != s2[i] || !s1[i] || !s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

void	freedouble(char **c)
{
	int	i;

	i = 0;
	if (!c)
		return ;
	while (c[i])
	{
		free(c[i]);
		i++;
	}
	free(c);
}
