/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   aliases.c                                         :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/08/28 18:10:22 by joppe         #+#    #+#                 */
/*   Updated: 2023/08/29 11:03:58 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line.h"
#include "libft.h"
#include "megashell.h"
#include "execute.h"
#include "test_utils.h"
#include <errno.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

static  t_alias alias_parse(char *line)
{

}

void aliases_init(t_meta *meta, char *file)
{
	int fd;
	char *line;


	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		printf("error opening [%s]\n", file);
		perror(strerror(errno));
		return;
	}


	const char *needle = "alias ";
	line = get_next_line(fd);
	while (line)
	{
		printf("aliases line: [%s]\n", line);

		if (ft_strnstr(line, needle, ft_strlen(needle)))
		{
			t_alias = alias_parse(line);
		}

		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}
