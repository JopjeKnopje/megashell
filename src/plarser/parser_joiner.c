/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   parser_joiner.c                                   :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/12/01 22:36:25 by joppe         #+#    #+#                 */
/*   Updated: 2023/12/12 16:44:15 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "plarser.h"
#include "test_utils.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

static void	pr_disable_empty_tokens(t_tok_list *tokens)
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

static int	pr_join(t_token *tok_base, t_token *tok_joinee)
{
	char	*s_joined;

	s_joined = sized_strjoin(tok_base->content, tok_base->content_len,
			tok_joinee->content, tok_joinee->content_len);
	if (!s_joined)
		return (0);
	if (tok_joinee->kind == TOKEN_ALLOC)
		free(tok_joinee->content);
	*tok_joinee = lx_token_set(TOKEN_UNUSED, NULL, 0);
	if (tok_base->kind == TOKEN_ALLOC)
		free(tok_base->content);
	*tok_base = lx_token_set(TOKEN_ALLOC, s_joined, ft_strlen(s_joined));
	return (1);
}

t_tok_list	*pr_joiner(t_tok_list *tokens)
{
	t_tok_list	*tail;
	t_token		*tok_base;
	t_token		*tok_joinee;

	pr_disable_empty_tokens(tokens);
	tail = lx_lstlast(tokens);
	while (tail)
	{
		tok_base = &tail->token;
		tok_joinee = &tail->next->token;
		if (tok_joinee && tok_base->padding == 0)
		{
			if (!pr_join(tok_base, tok_joinee))
				return (NULL);
		}
		tail = tail->prev;
	}
	return (tokens);
}
