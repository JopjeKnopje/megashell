/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   pipes_test.c                                      :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/09/23 00:46:31 by joppe         #+#    #+#                 */
/*   Updated: 2023/09/23 01:14:31 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipes_test.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#define SIZE 3


t_command *command_init(int i)
{
	t_command *content = ft_calloc(1, sizeof(t_command));
	content->id = i;

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

	if (cmd->data)
		printf("cmd->data: [%s]\n", cmd->data);
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

int pipes_test()
{
	t_test_list *list = list_init();

	list_loop(list);




	list_free(list);

	return 0;
}

