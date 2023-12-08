/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   lexer_list.c                                      :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/08/13 18:59:15 by joppe         #+#    #+#                 */
/*   Updated: 2023/12/08 10:22:02 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "plarser.h"
#include "test_utils.h"
#include <criterion/internal/ordered-set.h>
#include <stdio.h>

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

void lx_lst_free(t_tok_list *lst)
{

	t_tok_list *tmp = lst;
	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		// if (tmp->token.kind == TOKEN_ALLOC)
		// 	free(tmp->token.content);
		free(tmp);
	}

}

t_tok_list *lx_lst_replace_first(t_tok_list **lst, t_tok_list *insert)
{
	if (!lst || !insert)
		return (NULL);
	if (!*lst)
	{
		*lst = insert;
		return (*lst);
	}

	free(*lst);
	*lst = insert;
	// (*lst)->next->prev = *lst;
	return (*lst);
}
