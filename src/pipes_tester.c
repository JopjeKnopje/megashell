/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   pipes_tester.c                                    :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/09/23 01:25:11 by joppe         #+#    #+#                 */
/*   Updated: 2023/09/23 01:39:33 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>

#define SIZE 256

void first_cmd()
{
	printf("haiiii\n");
}


void mid_cmd()
{
	char *line = calloc(SIZE, sizeof(char));

	while (line)
	{
		bzero(line, SIZE);
		fgets(line, SIZE, stdin);
		if (*line)
			printf("GOT FROM STDIN: [%s]", line);
		else
			break;
	}
}

int main(int argc, char *argv[])
{
	(void) argv;

	if (argc == 2)
		first_cmd();
	else
		mid_cmd();
	return 0;
}
