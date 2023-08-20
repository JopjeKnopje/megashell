/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   parser_list.c                                     :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/08/20 00:11:49 by joppe         #+#    #+#                 */
/*   Updated: 2023/08/20 21:59:54 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "plarser.h"

t_cmd_list	*pr_lstlast(t_cmd_list *lst)
{
	t_cmd_list	*tmp;

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

void	pr_lstadd_back(t_cmd_list **lst, t_cmd_list *new)
{
	t_cmd_list	*last;

	if (!lst || !new)
		return ;
	if (!(*lst))
		*lst = new;
	else
	{
		last = pr_lstlast(*lst);
		last->next = new;
		new->prev = last;
	}
}

t_cmd_list	*pr_lstnew(t_cmd_frame content)
{
	t_cmd_list	*node;

	node = (t_cmd_list *) malloc(sizeof(t_cmd_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void pr_lst_free(t_cmd_list *lst)
{
	t_cmd_list *tmp = lst;
	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}

}
