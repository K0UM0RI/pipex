/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 22:31:32 by sbat              #+#    #+#             */
/*   Updated: 2025/02/03 22:31:35 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static void	joinwithslash(char **paths)
{
	int		i;
	char	*c;

	i = 0;
	while (paths[i])
	{
		c = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		if (!paths[i])
		{
			i++;
			while (paths[i])
				free(paths[i++]);
			i = 0;
			while (paths[i])
				free(paths[i++]);
			free(paths);
			free(c);
			return (perror("join fail"), exit(1));
		}
		free(c);
		i++;
	}
}

char	**getpaths(char **envr)
{
	int		i;
	int		j;
	char	**paths;

	j = 0;
	while (envr[j])
	{
		i = 0;
		while (envr[j][i] && envr[j][i] != '=')
			i++;
		if (!ft_strncmp("PATH=", envr[j], i + 1))
			break ;
		j++;
	}
	if (!envr[j])
		return (NULL);
	paths = ft_split(envr[j] + i + 1, ':');
	if (!paths)
		return (NULL);
	joinwithslash(paths);
	return (paths);
}

int	ifslash(char *av)
{
	while (*av)
	{
		if (*av == '/')
			return (1);
		av++;
	}
	return (0);
}

char	*checkpaths(char *av, char **paths)
{
	int		i;
	char	*c;

	i = 0;
	c = NULL;
	while (paths[i])
	{
		c = ft_strjoin(paths[i], av);
		if (!c)
			return (perror("join fail"), NULL);
		if (!access(c, F_OK | X_OK))
			return (c);
		free(c);
		c = NULL;
		i++;
	}
	return (c);
}

char	*getcmd(char *av, char **paths)
{
	char	*c;
	char	*error;

	c = NULL;
	error = "command not found, or isnt executable\n";
	if (!av || !*av)
		return (NULL);
	if (ifslash(av))
	{
		if (!access(av, F_OK | X_OK))
			return (ft_strdup(av));
		else
			return (write(2, error, ft_strlen(error)), NULL);
	}
	if (paths)
		c = checkpaths(av, paths);
	if (c)
		return (c);
	return (write(2, error, ft_strlen(error)), NULL);
}
