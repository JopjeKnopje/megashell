/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   parser_utils.c                                    :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <jboeve@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/12/12 16:48:09 by jboeve        #+#    #+#                 */
/*   Updated: 2023/12/12 18:39:50 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "plarser.h"

bool	pr_is_redirect(t_token_kind k)
{
	const bool	is_redir[TOKEN_COUNT] = {
	[TOKEN_UNUSED] = NULL,
	[TOKEN_QUOTE_SINGLE] = false,
	[TOKEN_QUOTE_DOUBLE] = false,
	[TOKEN_TEXT] = false,
	[TOKEN_PIPE] = false,
	[TOKEN_LESS_THAN] = true,
	[TOKEN_GREATER_THAN] = true,
	[TOKEN_APPEND] = true,
	[TOKEN_HEREDOC] = true,
	[TOKEN_BLOCK_DOLLAR] = false,
	[TOKEN_ERROR] = NULL,
	};

	return (is_redir[k]);
}

