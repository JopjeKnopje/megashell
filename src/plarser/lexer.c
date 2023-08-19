/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   lexer.c                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/07/31 16:57:13 by joppe         #+#    #+#                 */
/*   Updated: 2023/08/19 22:10:27 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "plarser.h"
#include <stdio.h>

static void lx_trim_space(char **cursor)
{
	while (*cursor && **cursor == ' ')
	{
		(*cursor)++;
	}
}

static t_token lx_next(char *s)
{
	t_token	t;

	if (*s == '\'' || *s == '\"')
		t = lx_tokenize_quote(s, *s);
	else if (*s == '$')
		t = lx_tokenize_dollar(s);
	else if (*s == '|')
		t = lx_token_set(TOKEN_PIPE, s, 1);

	else if (lx_is_redir_heredoc(s, TOKEN_HEREDOC))
		t = lx_token_set(TOKEN_HEREDOC, s, 2);
	else if (lx_is_redir_heredoc(s, TOKEN_APPEND))
		t = lx_token_set(TOKEN_APPEND, s, 2);

	else if (*s == '>')
		t = lx_token_set(TOKEN_GREATER_THAN, s, 1);
	else if (*s == '<')
		t = lx_token_set(TOKEN_LESS_THAN, s, 1);
	else
		t = lx_tokenize_text(s);

	return (t);
}


static t_tok_list *lx_list_add_token(t_tok_list **token_lst, t_token t)
{
	t_tok_list	*node;

	if (!token_lst)
	{
		*token_lst = lx_lstnew(t);
		if (!token_lst)
			return (NULL);
	}
	else
	{
		node = lx_lstnew(t);
		if (!node)
			return (NULL);
		lx_lstadd_back(token_lst, node);
	}
	return (*token_lst);
}

t_tok_list *lx_main(char *s)
{
	t_token	t;
	t_tok_list	*token_lst;

	token_lst = NULL;
	while (*s)
	{
		lx_trim_space(&s);
		if (!s[0])
			return (token_lst);
		t = lx_next(s);

		// TODO Error handling
		lx_list_add_token(&token_lst, t);
		s += t.content_len;
	}
	return (token_lst);
}
