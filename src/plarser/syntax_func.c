/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_func.c                                     :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 23:19:49 by joppe             #+#    #+#             */
/*   Updated: 2024/01/19 16:14:53 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "plarser.h"
#include <stdio.h>
#include <stdbool.h>

bool	sy_token_redir(t_tok_list *node)
{
	t_token_kind	k;

	if (!node->next)
		return (false);
	k = node->next->token.kind;
	if (k == TOKEN_TEXT || k == TOKEN_QUOTE_DOUBLE || k == TOKEN_QUOTE_SINGLE || k == TOKEN_ALLOC)
		return (true);
	return (false);
}

bool	sy_token_pipe(t_tok_list *node)
{
	if (!node->next || !node->prev)
		return (false);
	if (node->next->token.kind == TOKEN_PIPE)
		return (false);
	return (true);
}

bool	sy_token_variable(t_tok_list *node)
{
	(void) node;
	return (true);
}

bool	sy_token_pass(t_tok_list *node)
{
	(void) node;
	return (true);
}

bool	sy_token_err(t_tok_list *node)
{
	(void) node;
	return (false);
}
