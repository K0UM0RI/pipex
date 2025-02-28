/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipexbonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 22:49:27 by sbat              #+#    #+#             */
/*   Updated: 2025/02/09 02:24:45 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	heredocpull(t_files *files, char *limiter, int *i)
{
	char	*gnl;
	int		fd;

	fd = open(".tmp", O_CREAT | O_WRONLY, 0777);
	if (fd == -1)
		(perror("open fail"), exit(1));
	*i = 3;
	gnl = get_next_line(0, limiter);
	while (gnl)
	{
		write(fd, gnl, ft_strlen(gnl));
		free(gnl);
		gnl = get_next_line(0, limiter);
	}
	close(fd);
	fd = open(".tmp", O_RDONLY, 077);
	if (fd == -1)
		(perror("open fail"), exit(1));
	dup2(fd, 69);
	close(fd);
	files->file[0] = 69;
}

void	piping(t_files files, int ac, int i)
{
	close(0);
	close(1);
	if ((i == 2 && files.file[0] > 0) || (i == 3 && files.file[0] == 69))
		dup2(files.file[0], 0);
	else
		dup2(files.oldpipe[0], 0);
	if (i == ac - 2)
		dup2(files.file[1], 1);
	else
		dup2(files.pipefd[1], 1);
	(cleanfds(files.file, 2), cleanfds(files.pipefd, 2), cleanfds(files.oldpipe,
			2));
}

void	applycmd(t_files files, char *av, char **envr, int *child)
{
	files.paths = getpaths(envr);
	files.c = ft_split(av, ' ');
	if (!files.c)
		(freedouble(files.paths), free(child), exit(1));
	files.cmd = getcmd(files.c[0], files.paths);
	if (!files.cmd)
		(freedouble(files.c), freedouble(files.paths), free(child), exit(127));
	execve(files.cmd, files.c, envr);
	(perror("execve error"), freedouble(files.c), free(files.cmd),
		freedouble(files.paths), free(child), exit(1));
}

int	testeforhere_doc(t_files *files, int *i, char **av, int ac)
{
	files->oldpipe[0] = -1;
	files->oldpipe[1] = -1;
	if (ac < 5)
		(write(2, "invalid input\n", 14), exit(1));
	*i = 2;
	if (!ft_strncmp(av[1], "here_doc", ft_strlen(av[1])))
	{
		heredocpull(files, av[2], i);
		if (pipe(files->pipefd) == -1)
			(perror("pipe failure"), exit(1));
		files->oldpipe[0] = files->pipefd[0];
		files->oldpipe[1] = files->pipefd[1];
	}
	else
		initfiles(files, 0, av[1], *i);
	initfiles(files, 1, av[ac - 1], *i);
	return (*i);
}

int	main(int ac, char **av, char **envr)
{
	t_files	files;
	int		i;
	int		*child;
	int		end;

	end = testeforhere_doc(&files, &i, av, ac);
	child = (int *)malloc(sizeof(int) * ac);
	while (i < ac - 1)
	{
		if (pipe(files.pipefd) == -1)
			return (perror("pipe failure"), free(child), 1);
		child[i] = fork();
		if (((files.file[0] < 0 && i == 2) || (files.file[1] < 0 && i == ac
					- 2)) && !child[i])
			(piping(files, ac, i), free(child), exit(1));
		else if (!child[i])
			(piping(files, ac, i), applycmd(files, av[i], envr, child));
		else if (child[i] < 0)
			return (perror("fork failure"), cleanfds(files.pipefd, 2),
				cleanfds(files.oldpipe, 2), free(child), 1);
		else
			resetoldpipe(&files);
		i++;
	}
	return (finish(files, i, child, end));
}
