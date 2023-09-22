/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   pipes_list.c                                      :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/09/23 00:51:33 by joppe         #+#    #+#                 */
/*   Updated: 2023/09/23 01:06:10 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "pipes_test.h"
#include <stdio.h>
#include <stdlib.h>

t_test_list	*test_lstlast(t_test_list *lst)
{
	t_test_list	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (tmp)
	{
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}

void	test_lstadd_back(t_test_list **lst, t_test_list *new)
{
	t_test_list	*last;

	if (!lst || !new)
		return ;
	if (!(*lst))
		*lst = new;
	else
	{
		last = test_lstlast(*lst);
		last->next = new;
		new->prev = last;
	}
}

t_test_list	*test_lstnew(t_command *content)
{
	t_test_list	*node;

	node = (t_test_list *) malloc(sizeof(t_test_list));
	if (!node)
		return (NULL);
	node->cmd = content;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void test_lst_free(t_test_list *lst)
{
	t_test_list	*tmp;

	tmp = lst;
	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
}

void	test_lstiter(t_test_list *lst, void (*f)(t_test_list *))
{
	t_test_list	*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		f(tmp);
	}
}
