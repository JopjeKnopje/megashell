/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   space_count.c                                     :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <jboeve@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/29 14:13:28 by jboeve        #+#    #+#                 */
/*   Updated: 2023/11/29 17:18:52 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "plarser.h"

#include <stdio.h>

size_t sc_count(t_token *t)
{
	size_t i;

	i = t->content_len;
	while (t->content[i] && lx_is_metachar(t->content[i]))
	{
		i++;
	}
	i -= t->content_len;
	return i;
}

t_tok_list *sc_main(t_tok_list *tokens)
{
	t_tok_list *head;
	t_token_kind k;

	head = tokens;
	while (tokens)
	{
		k = tokens->token.kind;
		if (k == TOKEN_TEXT || k == TOKEN_BLOCK_QUOTE_DOUBLE || k == TOKEN_BLOCK_QUOTE_SINGLE || k == TOKEN_BLOCK_DOLLAR)
			tokens->token.padding = sc_count(&tokens->token);
		tokens = tokens->next;
	}
	return head;
}
