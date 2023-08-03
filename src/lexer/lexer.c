/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   lexer.c                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/07/31 16:57:13 by joppe         #+#    #+#                 */
/*   Updated: 2023/08/03 18:07:55 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "lexer.h"
#include "libft.h"

static t_token token_set(t_token_kind k, char *s, uint32_t len)
{
	t_token t;

	t.kind = k;
	t.content = s;
	t.content_len = len;

	return (t);
}

static t_token lexer_tokenize_quote(char *s, char c)
{
	uint32_t i = 1;

	while (s[i])
	{
		if (s[i] == c)
			return (token_set(TOKEN_QUOTE_SINGLE, s, i + 1));
		i++;
	}
	return (token_set(TOKEN_ERROR, s, 1));
}

static t_token lexer_next(t_lexer *l, char *s)
{
	t_token	t;

	if (*s == '\'')
		t = lexer_tokenize_quote(s, *s);
	else if (*s == '\"')
		t = lexer_tokenize_quote(s, *s);
	else
		t = token_set(TOKEN_UNKNOWN, s, 1);

	return (t);
}

void lexer(char *s)
{
	t_lexer	l;
	t_token	t;

	l.content = s;
	while (*l.content)
	{
		t = lexer_next(&l, l.content);
		printf("token [%.*s]\n", t.content_len, t.content);
		l.content += (t.content_len * sizeof(char));
	}
}
