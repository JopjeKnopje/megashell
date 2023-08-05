/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iris <iris@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:29:05 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/08/06 00:28:03 by iris             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

t_cmds	*create_mock_node(char *action[4])
{
	char	**new_array;
	t_cmds	*node;
	int		i = 3;

	node = malloc(sizeof(t_cmds));
	if (!node)
		return (NULL);
	new_array = ft_calloc(sizeof(char *), i + 1);
	i = 0;
	while (action[i])
	{
		new_array[i] = ft_strdup(action[i]);
		i++;
	}
	node->action = new_array;
	node->next = NULL;
	return (node);
}

void	add_to_end(t_cmds **list, t_cmds *new)
{
	t_cmds	*tmp;

	if (!list || !new)
		return ;
	if (!*list)
		*list = new;
	else
	{
		tmp = *list;
		while (tmp->next != '\0')
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_cmds	*mock_input(void)
{
	int		i;
	char	*action[3][4] = {{"cat", "-e", "MAKEFILE"}, {"wc", "-l"}, };
	t_cmds	*head = 0;

	i = 0;	

	while (i < 2)
	{
		add_to_end(&(head), create_mock_node(action[i]));
		i++;
	}
	return (head);
}
