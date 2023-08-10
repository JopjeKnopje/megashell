/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   lexer_utils.c                                     :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <marvin@42.fr>                       +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/08/04 15:11:36 by jboeve        #+#    #+#                 */
/*   Updated: 2023/08/10 13:29:36 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "libft.h"

static const char METACHARS[] = {
	'|',
	'<',
	'>',
	' ',
	'\t',
	'\n',
	'\0'
};

bool lexer_is_metachar(char c)
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

bool lexer_is_varchar(char c)
{
	return ((ft_isalpha(c) || c == '_') && !lexer_is_metachar(c));
}

bool lexer_is_valid_var_name(char *s)
{
	uint32_t	i;

	i = 0;
	if (!lexer_is_varchar(s[i]) || ft_isdigit(s[i]))
		return (false);
	while (s[i] && !lexer_is_metachar(s[i]))
	{
		if (!lexer_is_varchar(s[i]) && !ft_isdigit(s[i]))
			return (false);
		i++;
	}
	return (true);
}
