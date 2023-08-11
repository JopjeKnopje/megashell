/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   lexer.c                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/07/31 16:57:13 by joppe         #+#    #+#                 */
/*   Updated: 2023/08/12 01:08:55 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "lexer.h"
#include "libft.h"

static void lexer_trim_space(t_lexer *l)
{
	while (*l->cursor && *l->cursor == ' ')
	{
		l->cursor++;
	}
}
static t_token lexer_next(char *s)
{
	t_token	t;

	if (*s == '\'' || *s == '\"')
		t = lexer_tokenize_quote(s, *s);
	else if (*s == '$')
		t = lexer_tokenize_dollar(s);
	else if (*s == '|')
		t = token_set(TOKEN_PIPE, s, 1);
	else if (*s == '>')
		t = token_set(TOKEN_GREATER_THAN, s, 1);
	else if (*s == '<')
		t = token_set(TOKEN_LESS_THAN, s, 1);
	else
		t = lexer_tokenize_text(s);

	return (t);
}


static t_list *lexer_list_add_token(t_list **token_lst, t_token t)
{
	t_list	*node;
	t_token	*content;

	content = ft_calloc(sizeof(t_token), 1);
	if (!content)
		return (NULL);
	ft_memcpy(content, &t, sizeof(t_token));
	if (!token_lst)
	{
		*token_lst = ft_lstnew(content);
		if (!token_lst)
			return (NULL);
	}
	else
	{
		node = ft_lstnew(content);
		if (!node)
			return (NULL);
		ft_lstadd_back(token_lst, node);
	}
	return (*token_lst);
}

t_list *lexer(char *s)
{
	t_lexer	l;
	t_token	t;

	l.cursor = s;
	l.token_lst = NULL;
	while (*l.cursor)
	{
		lexer_trim_space(&l);
		if (!l.cursor[0])
			return (NULL);
		t = lexer_next(l.cursor);

		// TODO Error handling
		lexer_list_add_token(&l.token_lst, t);

		l.cursor += t.content_len;
	}
	return (l.token_lst);
}
