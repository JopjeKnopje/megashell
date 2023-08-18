/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   syntax_func.c                                     :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/08/18 23:19:49 by joppe         #+#    #+#                 */
/*   Updated: 2023/08/19 00:21:09 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "plarser.h"
#include <stdbool.h>

bool sy_token_redir(t_tok_list *node)
{
	t_token_kind k;

	if (!node->next)
		return (true);

	k = node->next->token.kind;
	if (k == TOKEN_TEXT || k == TOKEN_QUOTE_DOUBLE || k == TOKEN_QUOTE_SINGLE)
		return (false);

	return (true);
}

bool sy_token_quote(t_tok_list *node)
{
	return (false);
}

bool sy_token_pipe(t_tok_list *node)
{
	return (false);
}

bool sy_token_variable(t_tok_list *node)
{
	return (false);
}

bool sy_token_pass(t_tok_list *node)
{
	return (false);
}
