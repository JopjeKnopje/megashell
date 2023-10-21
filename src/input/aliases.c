/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   aliases.c                                         :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/08/28 18:10:22 by joppe         #+#    #+#                 */
/*   Updated: 2023/08/28 19:14:39 by joppe         ########   odam.nl         */
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
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>


#define PIPE_READ 0
#define PIPE_WRITE 1

void aliases_init(t_meta *meta)
{
	int to_child[2];
	int from_child[2];
	pipe(to_child);
	pipe(from_child);

	int pid = fork();
	if (pid == 0)
	{
		if (dup2(to_child[PIPE_READ], STDIN_FILENO) == -1)
		{
			perror(strerror(errno));
			printf("dup failed\n");
		}
		if (dup2(from_child[PIPE_WRITE], STDOUT_FILENO) == -1)
		{
			perror(strerror(errno));
			printf("dup failed\n");
		}
		close(to_child[PIPE_WRITE]);
		close(from_child[PIPE_READ]);


		char *argv[] = {
			"bash",
			"-i",
			NULL
		};
		execve("/usr/bin/bash", argv, meta->envp);
	}
	close(to_child[PIPE_READ]);
	close(from_child[PIPE_WRITE]);



	char *buf = "alias\n";
	write(to_child[PIPE_WRITE], buf, ft_strlen(buf));


	char *line = get_next_line(from_child[PIPE_READ]);
	while (line)
	{
		printf("from pipe [%s]\n", line);
		free(line);
	line = get_next_line(from_child[PIPE_READ]);
	}



	close(to_child[PIPE_WRITE]);

	close(from_child[PIPE_READ]);

	waitpid(pid, NULL, NULL);
}
