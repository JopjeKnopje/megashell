/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   sender.c                                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <marvin@42.fr>                       +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/07/27 12:58:49 by jboeve        #+#    #+#                 */
/*   Updated: 2023/07/27 13:42:56 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

bool running = true;

int get_pid()
{
	printf("target pid: ");
	char *line = NULL;
	size_t len = 0;
	ssize_t lineSize = 0;
	lineSize = getline(&line, &len, stdin);
	int pid = ft_atoi(line);

	printf("gnl [%d]\n", pid);

	return pid;
}

int main(int argc, char *argv[])
{
	int pid = get_pid();


	while (running)
	{
		printf("sending signal to %d\n", pid);
		kill(pid, SIGUSR1);
		sleep(1);
	}


	return (1);
}
