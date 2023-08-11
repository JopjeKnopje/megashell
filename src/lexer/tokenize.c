/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   tokenize.c                                        :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <marvin@42.fr>                       +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/08/07 17:43:17 by jboeve        #+#    #+#                 */
/*   Updated: 2023/08/11 16:22:23 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdbool.h>
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
	uint32_t i = 1;

	while (s[i])
	{
		if (s[i] == c)
			return (token_set(TOKEN_QUOTE_SINGLE, s, i + 1));
		i++;
	}
	return (token_set(TOKEN_ERROR, s, 1));
}

t_token lexer_tokenize_dollar(char *s)
{
	uint32_t	i;

	i = 1;
	if (!lexer_is_varchar(s[i]) || ft_isdigit(s[i]))
		return (token_set(TOKEN_ERROR, s, i));
	while (s[i] && !lexer_is_metachar(s[i]))
	{
		if (!lexer_is_varchar(s[i]) && !ft_isdigit(s[i]))
			return (token_set(TOKEN_ERROR, s, i));
		i++;
	}
	return (token_set(TOKEN_DOLLAR, s, i));
}
