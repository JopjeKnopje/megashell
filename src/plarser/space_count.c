/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   space_count.c                                     :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <jboeve@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/29 14:13:28 by jboeve        #+#    #+#                 */
/*   Updated: 2023/12/08 15:24:36 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "plarser.h"
#include <stdio.h>

size_t	sc_count(t_token *t)
{
	size_t	i;

	i = t->content_len;
	while (t->content[i] && t->content[i] == ' ')
	{
		i++;
	}
	i -= t->content_len;
	return i;
}

t_tok_list	*sc_main(t_tok_list *tokens)
{
	t_tok_list *const head = tokens;

	while (tokens)
	{
		if (tokens->next)
			tokens->token.padding = sc_count(&tokens->token);
		else
			tokens->token.padding = 0;
		tokens = tokens->next;
	}
	return head;
}
