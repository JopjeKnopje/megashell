/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   parser_joiner.c                                   :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/12/01 22:36:25 by joppe         #+#    #+#                 */
/*   Updated: 2023/12/01 23:24:41 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "plarser.h"
#include "utils.h"
#include <stdio.h>

// In-case we have an empty token set its state to TOKEN_UNUSED, so the parser will ignore it.
static void pr_disable_tokens(t_tok_list *tokens)
{
	while (tokens)
	{
		if (tokens->token.content_len == 0)
		{
			if (tokens->token.kind == TOKEN_ALLOC)
				free(tokens->token.content);
			tokens->token.kind = TOKEN_UNUSED;
		}
		tokens = tokens->next;	
	}
}

t_tok_list *pr_join_tokens(t_tok_list *tokens)
{
	t_tok_list	*tail;
	t_token		*tok_base;
	t_token		*tok_joinee;

	pr_disable_tokens(tokens);
	tail = lx_lstlast(tokens);
	while (tail)
	{
		tok_base = &tail->token;
		tok_joinee = &tail->next->token;
		if (tok_joinee && tok_base->padding == 0)
		{
			char	*joined = sized_strjoin(tok_base->content, tok_base->content_len,
					tok_joinee->content, tok_joinee->content_len);
			// printf("joined [%.*s] with [%.*s] == [%s]\n",
			// 		(int) tok_base->content_len, tok_base->content,
			// 		(int) tok_joinee->content_len, tok_joinee->content, joined);
			if (!joined)
				UNIMPLEMENTED("protect sized_strjoin");

			tok_joinee->kind = TOKEN_UNUSED;

			tok_base->content = joined;
			tok_base->content_len = ft_strlen(joined);
			tok_base->kind = TOKEN_ALLOC;
		}
		tail = tail->prev;
	}
	return (tokens);
}


