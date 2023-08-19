/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   syntax_func.c                                     :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/08/18 23:19:49 by joppe         #+#    #+#                 */
/*   Updated: 2023/08/19 23:41:03 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "plarser.h"
#include <stdbool.h>



// '>' <WORD>
// '<' <WORD>
// '>>' <WORD>
// '<<' <WORD>
// TODO Not sure about these.
// <NUMBER> '>' <WORD> 
// <NUMBER> '<' <WORD>
// <NUMBER> '>>' <WORD>
// <NUMBER> '<<' <WORD>

bool sy_token_redir(t_tok_list *node)
{
	t_token_kind k;

	if (!node->next)
		return (false);

	k = node->next->token.kind;
	if (k == TOKEN_TEXT || k == TOKEN_QUOTE_DOUBLE || k == TOKEN_QUOTE_SINGLE)
		return (true);

	return (false);
}

bool sy_token_pipe(t_tok_list *node)
{
	if (!node->next || !node->prev)
		return (false);
	if (node->next->token.kind == TOKEN_PIPE)
		return (false);
	return (true);
}

bool sy_token_variable(t_tok_list *node)
{
	(void) node;
	return (true);
}

bool sy_token_pass(t_tok_list *node)
{
	(void) node;
	return (true);
}

bool sy_token_err(t_tok_list *node)
{
	(void) node;
	return (false);
}
