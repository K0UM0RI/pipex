/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:21:33 by sbat              #+#    #+#             */
/*   Updated: 2025/02/04 23:57:20 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	finish(t_files files, int i, int *child, int end)
{
	int	status;

	(cleanfds(files.file, 2), cleanfds(files.pipefd, 2));
	while (end < i)
	{
		waitpid(child[end], &status, 0);
		end++;
	}
	return (WEXITSTATUS(status));
}

void	applycmd(t_files files, char *av, int i, char **envr)
{
	if (files.file[i] == -1)
		exit(1);
	files.paths = getpaths(envr);
	files.c = ft_split(av, ' ');
	if (!files.c)
		(freedouble(files.paths), exit(1));
	files.cmd = getcmd(files.c[0], files.paths);
	if (!files.cmd)
		(freedouble(files.c), freedouble(files.paths), exit(127));
	dup2(files.file[i], i);
	dup2(files.pipefd[i == 0], i == 0);
	cleanfds(files.file, 2);
	cleanfds(files.pipefd, 2);
	execve(files.cmd, files.c, envr);
	(perror("execve error"), freedouble(files.c), free(files.cmd),
		freedouble(files.paths), exit(1));
}

int	main(int ac, char **av, char **envr)
{
	int		child;
	t_files	files;
	int		child2;

	if (ac != 5)
		return (write(2, "Invalid input\n", 14), 1);
	initfiles(&files, 0, av[1], 2);
	initfiles(&files, 1, av[ac - 1], 2);
	if (pipe(files.pipefd) == -1)
		return (perror("pipe failure"), 1);
	(close(0), close(1));
	child = fork();
	if (!child)
		applycmd(files, av[2], 0, envr);
	child2 = fork();
	if (!child2)
		applycmd(files, av[3], 1, envr);
	return (finish(files, 2, (int []){child, child2}, 0));
}
