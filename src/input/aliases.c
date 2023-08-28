/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   aliases.c                                         :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/08/28 18:10:22 by joppe         #+#    #+#                 */
/*   Updated: 2023/08/28 18:57:27 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"
#include "megashell.h"
#include "execute.h"
#include "test_utils.h"
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>


#define PIPE_READ 0
#define PIPE_WRITE 1

void aliases_init(t_meta *meta)
{
	int file_fd = open("test_file.txt", O_RDONLY);
	if (file_fd == -1)
	{
		printf("failed opening file\n");
	}


	int pid = fork();
	if (pid == 0)
	{
		if (dup2(file_fd, STDIN_FILENO) == -1)
		{
			perror(strerror(errno));
			printf("dup failed\n");
		}

		char *argv[] = {
			"bash",
			NULL
		};
		execve("/usr/bin/bash", argv, meta->envp);
	}


	waitpid(pid, NULL, NULL);
	printf("done waiting\n");
	close(file_fd);
}
