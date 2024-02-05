/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                        :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: iris <iris@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 17:43:17 by jboeve            #+#    #+#             */
/*   Updated: 2024/01/16 13:41:45 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "plarser.h"
#include <stdio.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <stdint.h>
#include <limits.h>
#include "libft.h"

t_token	lx_token_set(t_token_kind k, char *s, uint32_t len)
{
	t_token	t;

	t.kind = k;
	t.content = s;
	t.content_len = len;
	t.padding = 0;
	return (t);
}

t_token	lx_tokenize_quote_block(char *s, char c)
{
	uint32_t		i;
	t_token_kind	k;

	i = 1;
	k = ((c == '\'') * TOKEN_QUOTE_SINGLE + (c == '\"') * TOKEN_QUOTE_DOUBLE);
	while (s[i])
	{
		if (s[i] == c)
			return (lx_token_set(k, s, i + 1));
		i++;
	}
	return (lx_token_set(TOKEN_ERROR, s, i));
}

static t_token	lx_iterate_potential_var(char *s, int i, t_token_kind k)
{
	bool	is_var;

	while (s[i] && !lx_is_metachar(s[i]))
	{
		if (s[i] == '$')
		{
			i++;
			continue ;
		}
		is_var = !lx_is_varchar(s[i]);
		if (is_var && !ft_isdigit(s[i]) && s[i] != ' ' && s[i] != '?')
			k = TOKEN_ERROR;
		i++;
	}
	return (lx_token_set(k, s, i));
}

t_token	lx_tokenize_dollar_block(char *s)
{
	size_t			i;
	t_token_kind	k;

	i = 0;
	while (s[i] == '$')
		i++;
	k = ((i != 1) * TOKEN_ERROR) + ((i == 1) * TOKEN_TEXT);
	if (!s[i] || lx_is_metachar(s[i]))
		return (lx_token_set(k, s, i));
	k = TOKEN_BLOCK_DOLLAR;
	if (s[i] && !lx_is_valid_var_char(s[i], true))
		k = TOKEN_ERROR;
	return (lx_iterate_potential_var(s, i, k));
}

t_token	lx_tokenize_text(char *s)
{
	size_t	i;
	bool	is_meta;

	i = 0;
	is_meta = s[i] != '$' && s[i] != '\'' && s[i] != '\"';
	while (s[i] && s[i] != ' ' && !lx_is_metachar(s[i]) && is_meta)
	{
		i++;
		is_meta = s[i] != '$' && s[i] != '\'' && s[i] != '\"';
	}
	return (lx_token_set(TOKEN_TEXT, s, i));
}
