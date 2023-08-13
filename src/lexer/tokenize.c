/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   tokenize.c                                        :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <marvin@42.fr>                       +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/08/07 17:43:17 by jboeve        #+#    #+#                 */
/*   Updated: 2023/08/13 13:00:59 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "libft.h"

t_token token_set(t_token_kind k, char *s, uint32_t len)
{
	t_token t;

	t.kind = k;
	t.content = s;
	t.content_len = len;

	return (t);
}

t_token lexer_tokenize_quote(char *s, char c)
{
	uint32_t i;
	t_token_kind k;

	i = 1;
	k = (c == '\'') * TOKEN_QUOTE_SINGLE + (c == '\"') * TOKEN_QUOTE_DOUBLE;
	while (s[i])
	{
		if (s[i] == c)
			return (token_set(k, s, i + 1));
		i++;
	}
	return (token_set(TOKEN_ERROR, s, i));
}

t_token lexer_tokenize_dollar(char *s)
{
	uint32_t		i;
	t_token_kind	k;

	// Nasty hack
	i = 1;
	while (s[1] == '?' && s[i] && !lexer_is_metachar(s[i]))
	{
		i++;
	}
	if (i == 2)
		return (token_set(TOKEN_DOLLAR, s, i));
	i = 1;
	k = TOKEN_DOLLAR;
	if ((!lexer_is_varchar(s[i]) || ft_isdigit(s[i])))
		k = TOKEN_ERROR;
	while (s[i] && !lexer_is_metachar(s[i]))
	{
		if (!lexer_is_varchar(s[i]) && !ft_isdigit(s[i]))
			k = TOKEN_ERROR;
		i++;
	}
	return (token_set(k, s, i));
}

t_token lexer_tokenize_text(char *s)
{
	int32_t i;

	i = 0;
	while (s[i] && s[i] != ' ' && !lexer_is_metachar(s[i]))
	{
		i++;
	}
	return (token_set(TOKEN_TEXT, s, i));
}
