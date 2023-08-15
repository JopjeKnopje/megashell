/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   parser_list.c                                     :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/08/13 18:59:15 by joppe         #+#    #+#                 */
/*   Updated: 2023/08/15 23:52:09 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

t_cf_list	*pr_lstlast(t_cf_list *lst)
{
	t_cf_list	*tmp;

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

void	pr_lstadd_back(t_cf_list **lst, t_cf_list *new)
{
	t_cf_list	*last;

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

void pr_lst_free(t_cf_list *lst, void (*func)(t_cf_list *node))
{

	t_cf_list *tmp = lst;
	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		if (func)
			(*func)(tmp);
		free(tmp);
	}
}

t_cf_list	*pr_lstnew(t_command_frame content)
{
	t_cf_list	*node;

	node = (t_cf_list *) malloc(sizeof(t_cf_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_cf_list *pr_list_add_token(t_cf_list **cf_list, t_command_frame frame)
{
	t_cf_list	*node;

	if (!cf_list)
	{
		*cf_list = pr_lstnew(frame);
		if (!cf_list)
			return (NULL);
	}
	else
	{
		node = pr_lstnew(frame);
		if (!node)
			return (NULL);
		pr_lstadd_back(cf_list, node);
	}
	return (*cf_list);
}

