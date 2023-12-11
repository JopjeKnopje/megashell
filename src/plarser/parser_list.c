/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 00:11:49 by joppe             #+#    #+#             */
/*   Updated: 2023/12/11 17:38:58 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "plarser.h"
#include "utils.h"

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

void	pr_lst_free(t_cmd_list *lst)
{
	t_cmd_list	*tmp;

	tmp = lst;
	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		if (tmp->content.argv)
			str_free_2d(tmp->content.argv);
		if (tmp->content.infile)
			free(tmp->content.infile);
		if (tmp->content.outfile)
			free(tmp->content.outfile);
		if (tmp->content.heredoc_delim)
			free(tmp->content.heredoc_delim);
		free(tmp);
	}
}

size_t	pr_lst_count(t_cmd_list *lst)
{
	size_t	count;

	count = 0;
	while (lst)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}
