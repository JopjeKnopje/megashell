/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   lexer_utils.c                                     :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <marvin@42.fr>                       +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/08/04 15:11:36 by jboeve        #+#    #+#                 */
/*   Updated: 2023/08/19 22:12:45 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <readline/history.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "libft.h"
#include "plarser.h"

static const char METACHARS[] = {
	'|',
	'<',
	'>',
	' ',
	'\t',
	'\n',
	'\0'
};

bool lx_is_metachar(char c)
{
	uint32_t i = 0;

	while (METACHARS[i])
	{
		if (c == METACHARS[i])	
			return (true);
		i++;
	}
	return (false);
}

bool lx_is_varchar(char c)
{
	return ((ft_isalpha(c) || c == '_') && !lx_is_metachar(c));
}

bool lx_is_valid_var_name(char *s)
{
	uint32_t	i;

	i = 0;
	if (!lx_is_varchar(s[i]) || ft_isdigit(s[i]))
		return (false);
	while (s[i] && !lx_is_metachar(s[i]))
	{
		if (!lx_is_varchar(s[i]) && !ft_isdigit(s[i]))
			return (false);
		i++;
	}
	return (true);
}

bool lx_is_redir_heredoc(char *s, t_token_kind k)
{
	int32_t i = 0;
	char c;
	if (k == TOKEN_APPEND)
		c = '>';
	else if (k == TOKEN_HEREDOC)
		c = '<';
	while (s[i] && s[i] == c)
	{
		i++;
	}
	// printf("i: %d\n", i);
	return (i == 2);
}
