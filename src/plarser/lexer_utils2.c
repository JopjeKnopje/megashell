/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:03:36 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/12/11 17:04:05 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "libft.h"
#include "plarser.h"

bool	lx_is_redir_heredoc(char *s, t_token_kind k)
{
	int32_t	i;
	char	c;

	i = 0;
	if (k == TOKEN_APPEND)
		c = '>';
	else if (k == TOKEN_HEREDOC)
		c = '<';
	while (s[i] && s[i] == c)
	{
		i++;
	}
	return (i == 2);
}
