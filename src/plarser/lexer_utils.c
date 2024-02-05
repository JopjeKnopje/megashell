/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                     :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 15:11:36 by jboeve            #+#    #+#             */
/*   Updated: 2024/01/16 12:37:35 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "libft.h"
#include "plarser.h"

static char	get_metachars(int i)
{
	static const char	metachars[] = { 
		'|',
		'<',
		'>',
		' ',
		'\t',
		'\v',
		'\n',
		'\0'
	};

	return (metachars[i]);
}

bool	lx_is_metachar(char c)
{
	uint32_t	i;

	i = 0;
	while (get_metachars(i))
	{
		if (c == get_metachars(i))
			return (true);
		i++;
	}
	return (false);
}

bool	lx_is_varchar(char c)
{
	return ((ft_isalpha(c) || c == '_') && !lx_is_metachar(c));
}

bool	lx_is_valid_var_char(char c, bool first_letter)
{
	if (first_letter)
		return ((ft_isalpha(c) || c == '_' || c == '?' || \
			c == '$') && !ft_isdigit(c) && !lx_is_metachar(c));
	else
		return ((ft_isalpha(c) || ft_isdigit(c) || c == '_') \
			&& !lx_is_metachar(c) && c != '$');
}

bool	lx_is_valid_var_name(char *s)
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
