/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   aliases_list.c                                    :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/08/29 10:41:51 by joppe         #+#    #+#                 */
/*   Updated: 2023/08/29 11:02:38 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "aliases.h"
#include "megashell.h"

t_alias_list *al_list_add_alias(t_alias_list **alias_list, t_alias alias)
{
	t_alias_list	*node;

	if (!alias_list)
	{
		*alias_list = al_lstnew(alias);
		if (!alias_list)
			return (NULL);
	}
	else
	{
		node = al_lstnew(alias);
		if (!node)
			return (NULL);
		al_lstadd_back(alias_list, node);
	}
	return (*alias_list);
}

t_alias_list	*al_lstlast(t_alias_list *lst)
{
	t_alias_list	*tmp;

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

void	al_lstadd_back(t_alias_list **lst, t_alias_list *new)
{
	t_alias_list	*last;

	if (!lst || !new)
		return ;
	if (!(*lst))
		*lst = new;
	else
	{
		last = al_lstlast(*lst);
		last->next = new;
	}
}

t_alias_list	*al_lstnew(t_alias content)
{
	t_alias_list	*node;

	node = (t_alias_list *) malloc(sizeof(t_alias_list));
	if (!node)
		return (NULL);
	node->alias = content;
	node->next = NULL;
	return (node);
}

void al_lst_free(t_alias_list *lst)
{

	t_alias_list *tmp = lst;
	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}

}


