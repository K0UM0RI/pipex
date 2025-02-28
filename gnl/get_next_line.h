/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbat <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:22:25 by sbat              #+#    #+#             */
/*   Updated: 2024/11/22 09:47:56 by sbat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# include "../pipex.h"
# ifndef BUFFER_SIZE

#  define BUFFER_SIZE 7

# endif

void		*ft_calloc(size_t nmemb, size_t size);
char		*ft_strjoingnl(char *s1, char *s2, int er);
int			ft_strchr(char *s, int c);
char		*ft_strdup(const char *s);
char		*get_next_line(int fd, char *limiter);
char		*freestr(char *str);
int			ft_strcpy(char *dest, char *src);

#endif
