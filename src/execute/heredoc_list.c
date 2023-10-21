/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   heredoc_list.c                                    :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <jboeve@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/17 14:43:47 by jboeve        #+#    #+#                 */
/*   Updated: 2023/10/21 21:33:06 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include <unistd.h>

t_hd_list	*hd_lstlast(t_hd_list *lst)
{
	t_hd_list	*tmp;

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

void	hd_lstadd_back(t_hd_list **lst, t_hd_list *new)
{
	t_hd_list	*last;

	if (!lst || !new)
		return ;
	if (!(*lst))
		*lst = new;
	else
	{
		last = hd_lstlast(*lst);
		last->next = new;
	}
}

t_hd_list *hd_lstremove_first(t_hd_list **lst)
{
	t_hd_list	*first;

	if (!lst || !*lst)
		return (NULL);
	first = *lst;
	*lst = (*lst)->next;
	first->next = NULL;
	return (first);
}

t_hd_list	*hd_lstnew(int fd)
{
	t_hd_list	*node;

	node = (t_hd_list *) malloc(sizeof(t_hd_list));
	if (!node)
		return (NULL);
	node->fd = fd;
	node->next = NULL;
	return (node);
}

void hd_lst_free(t_hd_list *lst)
{
	t_hd_list *tmp = lst;

	if (!lst)
		return;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
}
