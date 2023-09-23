/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   pipes_test.c                                      :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/09/23 00:46:31 by joppe         #+#    #+#                 */
/*   Updated: 2023/09/23 01:56:32 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipes_test.h"
#include "execute.h"
#include "libft.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/wait.h>
#include <unistd.h>

#define SIZE 3


t_command *command_init(int i)
{
	t_command *content = ft_calloc(1, sizeof(t_command));
	content->id = i;

	if (i == 1)
		content->content = strdup("/usr/bin/ls");
	if (i == 2)
		content->content = strdup("/usr/sbin/ifconfig");
	if (i == 3)
		content->content = strdup("/usr/bin/cat");

	return content;
}

t_test_list *list_init()
{
	t_test_list *list = NULL;

	for (int i = 0; i < SIZE; i++)
	{
		t_command *cmd = command_init(i + 1);
		test_lstadd_back(&list, test_lstnew(cmd));
	}
	return list;
}


void command_print(t_command *cmd)
{
	if (cmd->id)
		printf("cmd->id: [%d]\n", cmd->id);
	else
		printf("cmd->id: [NOT_SET]\n");

	if (cmd->content)
		printf("cmd->data: [%s]\n", cmd->content);
	else
		printf("cmd->data: \t[NOT_SET]\n");

	if (cmd->pipe[0])
		printf("cmd->pipe[READ]: \t[%d]\n", cmd->pipe[0]);
	else
		printf("cmd->pipe[READ]: [NOT_SET]\n");

	if (cmd->pipe[1])
		printf("cmd->pipe[WRITE]: [%d]\n", cmd->pipe[1]);
	else
		printf("cmd->pipe[WRITE]: [NOT_SET]\n");
	printf("--------------------------\n");

}

void list_loop(t_test_list *list)
{
	while (list)
	{
		command_print(list->cmd);
		list = list->next;
	}
}

void list_free(t_test_list *list)
{
	while (list)
	{
		t_test_list *tmp = list;
		list = list->next;
		free(tmp->cmd);
		free(tmp);
	}
}

// while (cmds)
// {
// 	if (pipe(cmds->pipe) == -1)
// 	{
// 		print_error(get_error_name(ERROR_PIPE));
// 		return ;
// 	}
// 	execute->pid = fork();
// 	if (execute->pid == -1) /* fork returns -1 in case of error */
// 	{
// 		print_error(get_error_name(ERROR_FORK));
// 		return ;
// 	}
// 	if (execute->pid == 0) /* fork returns 0 for child process */
// 	{
// 		// if this is not the first command in our list,
// 		// attach the prev->pipe to the STDIN, so we can read from the previous process.
// 		if (cmds->prev)
// 			dup2(cmds->prev->pipe[PIPE_READ], STDIN_FILENO);
//
// 		// if this is not the last command attach the STDOUT,
// 		// so the next command can attach it to its STDIN.
// 		// just like we are doing above.
// 		if (cmds->next)
// 			dup2(cmds->pipe[PIPE_WRITE], STDOUT_FILENO);
//
// 		children_spawn(meta, cmds);
// 		exit(69);
// 	}
//
// 	// always close the pipe in the main proc, since they will only be used between the procs them selves.
// 	close(cmds->pipe[PIPE_READ]);
// 	close(cmds->pipe[PIPE_WRITE]);
//
// 	cmds = cmds->next;
// }
//
void list_execute(t_test_list *list)
{
	int pid;

	while (list)
	{
		if (list->next)
			pipe(list->cmd->pipe);

		pid = fork();
		if (pid == 0)
		{
			if (list->prev)
			{
				dup2(list->prev->cmd->pipe[PIPE_READ], STDIN_FILENO);
				close(list->prev->cmd->pipe[PIPE_READ]);
			}

			if (list->next)
			{
				dup2(list->cmd->pipe[PIPE_WRITE], STDOUT_FILENO);
				close(list->prev->cmd->pipe[PIPE_WRITE]);
			}


			char *argv[] = { list->cmd->content, NULL };
       		if (execve(list->cmd->content, argv, NULL) == -1)
			{
				perror(strerror(errno));
				exit(68);
			}
			exit(69);
		}
		// main
		close(list->cmd->pipe[PIPE_READ]);
		close(list->cmd->pipe[PIPE_WRITE]);

		list = list->next;
	}
	int status;
	waitpid(pid, &status, 0);
	printf("last exitcode: %d\n", WEXITSTATUS(status));
}

int pipes_test()
{
	t_test_list *list = list_init();

	list_loop(list);

	list_execute(list);



	list_free(list);

	return 0;
}

