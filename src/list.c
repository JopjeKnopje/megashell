/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:29:05 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/08/11 16:57:57 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

t_cmd_list	*create_mock_node(char *action[4])
{
	char		**new_array;
	t_cmd_list	*node;
	int		i = 3;

	node = malloc(sizeof(t_cmd_list));
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

void	add_to_end(t_cmd_list **list, t_cmd_list *new)
{
	t_cmd_list	*tmp;

	if (!list || !new)
		return ;
	if (!*list)
	{
		*list = new;
		(*list)->prev = *list;
	}
	else
	{
		tmp = *list;
		while (tmp->next != '\0')
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
}

t_cmd_list	*mock_input(void)
{
	int			i;
	char		*action[3][4] = {{"pwd", "-e", "MAKEFILE"}, {"wc", "-l"}, };
	t_cmd_list	*head = 0;

	i = 0;
	while (i < 2)
	{
		add_to_end(&(head), create_mock_node(action[i]));
		i++;
	}
	return (head);
}
