/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 18:59:15 by joppe             #+#    #+#             */
/*   Updated: 2023/12/11 17:06:14 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "plarser.h"

t_tok_list	*lx_lstlast(t_tok_list *lst)
{
	t_tok_list	*tmp;

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

void	lx_lstadd_back(t_tok_list **lst, t_tok_list *new)
{
	t_tok_list	*last;

	if (!lst || !new)
		return ;
	if (!(*lst))
		*lst = new;
	else
	{
		last = lx_lstlast(*lst);
		last->next = new;
		new->prev = last;
	}
}

t_tok_list	*lx_lstnew(t_token content)
{
	t_tok_list	*node;

	node = (t_tok_list *) malloc(sizeof(t_tok_list));
	if (!node)
		return (NULL);
	node->token = content;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	lx_lst_free(t_tok_list *lst)
{
	t_tok_list	*tmp;

	tmp = lst;
	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
}
