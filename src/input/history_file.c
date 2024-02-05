/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   history_file.c                                    :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <marvin@42.fr>                       +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/08/15 17:00:05 by jboeve        #+#    #+#                 */
/*   Updated: 2024/01/26 15:45:34 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include "get_next_line.h"
#include "libft.h"
#include <stdbool.h>
#include <stdio.h>
#include <fcntl.h>
#include <readline/history.h>
#include <sys/fcntl.h>
#include <unistd.h>

static void	hs_replace_char(char *s, char delim)
{
	while (*s)
	{
		if (*s == delim)
			*s = 0;
		s++;
	}
}

bool	hs_read_history_file(char *file)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (false);
	line = get_next_line(fd);
	while (line)
	{
		hs_replace_char(line, '\n');
		add_history(line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (true);
}

bool	hs_add_history_file(char *file, char *line)
{
	int	fd;

	fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (!fd)
	{
		perror("History file open failed");
		return (false);
	}
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	close(fd);
	return (true);
}
