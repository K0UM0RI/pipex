/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipexbonus_extras.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 02:29:47 by sbat              #+#    #+#             */
/*   Updated: 2025/02/09 02:30:21 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	resetoldpipe(t_files *files)
{
	cleanfds(files->oldpipe, 2);
	files->oldpipe[0] = files->pipefd[0];
	files->oldpipe[1] = files->pipefd[1];
}

int	finish(t_files files, int i, int *child, int end)
{
	int	status;

	(cleanfds(files.file, 2), cleanfds(files.pipefd, 2));
	while (end < i)
	{
		waitpid(child[end], &status, 0);
		end++;
	}
	free(child);
	if (files.file[0] == 69)
		unlink(".tmp");
	return (WEXITSTATUS(status));
}
