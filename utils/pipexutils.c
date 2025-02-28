/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipexutils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 02:40:34 by sbat              #+#    #+#             */
/*   Updated: 2025/02/09 02:40:39 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	cleanfds(int *fds, int count)
{
	count--;
	while (count >= 0)
	{
		if (fds[count] > 0)
			close(fds[count]);
		count--;
	}
}

void	initfiles(t_files *files, int i, char *av, int d)
{
	char	*c;

	if (i == 0)
	{
		files->file[i] = open(av, O_RDONLY, 0777);
		c = ft_strjoin("input ", "file open failure");
	}
	else
	{
		if (d == 2)
			d = O_TRUNC;
		else
			d = O_APPEND;
		files->file[i] = open(av, O_CREAT | O_RDWR | d, 0777);
		c = ft_strjoin("output ", "file open failure");
	}
	if (files->file[i] == -1)
		perror(c);
	free(c);
}
