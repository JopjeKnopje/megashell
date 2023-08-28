/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   aliases.c                                         :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/08/28 18:10:22 by joppe         #+#    #+#                 */
/*   Updated: 2023/08/28 22:23:51 by joppe         ########   odam.nl         */
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

	
	uint32_t size = 256;
	char read_data[size];

	
	while (true)
	{
		ft_bzero(&read_data, size);
		int err = read(from_child[PIPE_READ], &read_data, size - 1);

		const char *needle = "exit";
		if (ft_strnstr(read_data, needle, ft_strlen(read_data)))
		{
			fprintf(stderr, "YUPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP\n");
			break;
		}
		// printf("%s", read_data);
		if (err < size - 1)
		{
			break;
		}
	}



	close(to_child[PIPE_WRITE]);
	close(from_child[PIPE_READ]);

	waitpid(pid, NULL, 0);
}
