/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   syntax.c                                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/08/18 21:20:04 by joppe         #+#    #+#                 */
/*   Updated: 2023/08/19 22:54:36 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "plarser.h"
#include "test_utils.h"
#include <math.h>
#include <signal.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>



typedef bool	(*t_syntax_func) (t_tok_list *t_cur);

static t_tok_list *sy_foward_list(t_tok_list *tokens, uint32_t skip)
{
	while (tokens && skip)
	{
		skip--;
		tokens = tokens->next;
	}
	return (tokens);
}

t_syntax_error sy_main(t_tok_list *tokens)
{
	const t_syntax_func	funcs[TOKEN_COUNT] = {
		[TOKEN_UNKNOWN] 		=	NULL,
		[TOKEN_QUOTE_SINGLE]	=	sy_token_pass,
		[TOKEN_QUOTE_DOUBLE]	=	sy_token_pass,
		[TOKEN_TEXT]			=	sy_token_pass,
		[TOKEN_PIPE] 			=	sy_token_pipe,
		[TOKEN_LESS_THAN] 		=	sy_token_redir,
		[TOKEN_GREATER_THAN]	=	sy_token_redir,
		[TOKEN_APPEND] 			=	sy_token_redir,
		[TOKEN_HEREDOC]			=	sy_token_redir,
		[TOKEN_DOLLAR] 			=	sy_token_variable,
		[TOKEN_ERROR]			=	NULL,
	};

	while (tokens)
	{
		if (!(*funcs[tokens->token.kind])(tokens))
		{
			printf("syntax error\n");
			print_token(tokens->token);
		}
		tokens = tokens->next;
	}

	return (lx_token_set(TOKEN_UNKNOWN, NULL, 0));
}
