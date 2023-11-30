/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   space_count.c                                     :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <jboeve@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/29 14:13:28 by jboeve        #+#    #+#                 */
/*   Updated: 2023/11/30 12:59:56 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "plarser.h"

#include <stdio.h>

size_t sc_count(t_token *t)
{
	size_t i;

	i = t->content_len;
	while (t->content[i] && t->content[i] == ' ')
	{
		i++;
	}
	i -= t->content_len;
	return i;
}

t_tok_list *sc_main(t_tok_list *tokens)
{
	t_tok_list *head;

	head = tokens;
	while (tokens)
	{
		tokens->token.padding = sc_count(&tokens->token);
		tokens = tokens->next;
	}
	return head;
}
