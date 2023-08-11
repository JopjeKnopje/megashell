/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   lexer.c                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/07/31 16:57:13 by joppe         #+#    #+#                 */
/*   Updated: 2023/08/11 17:37:49 by joppe         ########   odam.nl         */
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

void lexer(char *s)
{
	t_lexer	l;
	t_token	t;

	l.cursor = s;
	while (*l.cursor)
	{
		lexer_trim_space(&l);
		if (!l.cursor[0])
			return;
		t = lexer_next(l.cursor);

		printf("\x1b[36;49m");
		printf("lexer_content [%s]\n", l.cursor);
		printf("token_kind %s | token_content [%.*s] | token_content_len [%d]\n", TOKEN_NAMES[t.kind], t.content_len, t.content, t.content_len);
		printf("\x1b[0m");

		l.cursor += t.content_len;
	}
}
