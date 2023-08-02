/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   lexer.c                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/07/31 16:57:13 by joppe         #+#    #+#                 */
/*   Updated: 2023/08/02 18:50:58 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
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

static t_token lexer_tokenize_quote(char *s)
{
	t_token t;
	uint32_t i;

	i = 1;
	while (s[i] && s[i] != '\'')
	{
		i++;
	}
	t = token_set(TOKEN_QUOTE_SINGLE, s, i + 1);
	return (t);
}

static t_token lexer_next(t_lexer *l, char *s)
{
	t_token	t;

	if (*s == '\'')
		t = lexer_tokenize_quote(s);
	else if (*s == '\"')
		t = token_set(TOKEN_QUOTE_DOUBLE, s, 1);
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
		t = lexer_next(&l, s);
		printf("token_kind %s | token_content_len [%d] | token_content [%.*s]\n", TOKEN_NAMES[t.kind], t.content_len, t.content_len, t.content);
		printf("lexer_content [%s]\n", l.content);
		l.content += t.content_len;
	}
}
