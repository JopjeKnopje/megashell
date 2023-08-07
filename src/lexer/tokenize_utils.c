/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   tokenize_utils.c                                  :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <marvin@42.fr>                       +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/08/07 18:06:38 by jboeve        #+#    #+#                 */
/*   Updated: 2023/08/07 19:18:36 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

bool tokenize_is_valid_var_name(char *s)
{
	uint32_t		i;

	i = 1;
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
