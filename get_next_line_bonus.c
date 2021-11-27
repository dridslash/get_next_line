/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaqqad <mnaqqad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 14:33:05 by mnaqqad           #+#    #+#             */
/*   Updated: 2021/11/27 15:27:23 by mnaqqad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

static void	ft_free(char **s1, char **s2)
{
	free(*s1);
	*s1 = NULL;
	free(*s2);
	*s2 = NULL;
}

static void	ft_freesmall(char **s1)
{
	free(*s1);
	*s1 = NULL;
}

static void	ft_next(char **buffer, char **sline, char **saver, int fd)
{
	char	*tmp;
	ssize_t	holder;

	holder = 1;
	while (holder && ft_strchr((*saver), '\n') == -1)
	{
		holder = read(fd, (*buffer), BUFFER_SIZE);
		(*buffer)[holder] = '\0';
		(*saver) = ft_strjoin((*saver), (*buffer));
	}
	free(*buffer);
	if (holder == 0)
	{
		(*sline) = ft_strdup(*saver);
		ft_freesmall(saver);
	}
	else
	{
		(*sline) = ft_substr((*saver), 0, ft_strchr((*saver), '\n') + 1);
		tmp = (*saver);
		(*saver) = ft_strdup((*saver) + ft_strchr((*saver), '\n') + 1);
		free(tmp);
	}
	if (!(*(*sline)))
		ft_free(saver, sline);
}

char	*get_next_line(int fd)
{
	static char	*saver[1024];
	char		*buffer;
	char		*sline;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
		buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	if (read(fd, buffer, 0) == -1)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	if (!saver[fd])
		saver[fd] = ft_strdup("");
	ft_next(&buffer, &sline, &saver[fd], fd);
	return (sline);
}
