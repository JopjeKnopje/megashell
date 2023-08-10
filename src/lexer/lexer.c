/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   lexer.c                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/07/31 16:57:13 by joppe         #+#    #+#                 */
/*   Updated: 2023/08/10 23:10:22 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "lexer.h"

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
	// TODO Check if is var
	// blabla=
	// $blabla
	// TODO Have a function that checks if there is a variable present.
	else if (lexer_is_valid_var_name(s))
	{
		printf("valid name\n");
		t = lexer_tokenize_variable(s);
	}
	else
		t = token_set(TOKEN_UNKNOWN, s, 1);

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
		printf("\x1b[36;49m");
		printf("lexer_content [%s]\n", l.cursor);
		t = lexer_next(l.cursor);
		printf("token_kind %s | token_content [%.*s] | token_content_len [%d]\n", TOKEN_NAMES[t.kind], t.content_len, t.content, t.content_len);
		printf("\x1b[0m");
		l.cursor += (t.content_len * sizeof(char));
	}
}
