/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:21:41 by sbat              #+#    #+#             */
/*   Updated: 2025/02/03 22:48:50 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# define STDIN 100
# define STDOUT 200
# define STDERROR 300
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# define PID_MAX 1024

typedef struct s_files
{
	int		file[2];
	int		pipefd[2];
	int		oldpipe[2];
	char	**paths;
	char	**c;
	char	*cmd;
}			t_files;

// getcmd
char		**getpaths(char **envr);
char		*getcmd(char *av, char **paths);

// utils_utils
int			ft_strcmp(char *s1, char *s2);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
char		*ft_strdup(const char *s);
size_t		ft_strlen(const char *s);

// utils
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strjoin(char const *s1, char const *s2);
char		**ft_split(char const *s, char c);
void		freedouble(char **c);

// pipexbonusextras
void		cleanfds(int *fds, int count);
void		resetoldpipe(t_files *files);
int			finish(t_files files, int i, int *child, int end);
void		initfiles(t_files *files, int i, char *av, int d);

char		*get_next_line(int fd, char *limiter);

#endif
