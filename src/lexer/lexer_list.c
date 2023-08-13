/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   lexer_list.c                                      :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/08/13 18:59:15 by joppe         #+#    #+#                 */
/*   Updated: 2023/08/13 20:18:29 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token_list	*lx_lstlast(t_token_list *lst)
{
	t_token_list	*tmp;

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

void	lx_lstadd_back(t_token_list **lst, t_token_list *new)
{
	t_token_list	*last;

	if (!lst || !new)
		return ;
	if (!(*lst))
		*lst = new;
	else
	{
		last = lx_lstlast(*lst);
		last->next = new;
	}
}

t_token_list	*lx_lstnew(t_token content)
{
	t_token_list	*node;

	node = (t_token_list *) malloc(sizeof(t_token_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}