/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   syntax.c                                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/08/18 21:20:04 by joppe         #+#    #+#                 */
/*   Updated: 2023/11/06 20:08:26 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "plarser.h"

typedef bool	(*t_syntax_func) (t_tok_list *t_cur);

t_tok_list *sy_main(t_tok_list *tokens)
{
	const t_syntax_func	funcs[TOKEN_COUNT] = {
		[TOKEN_UNKNOWN] 		=	sy_token_unknown,
		[TOKEN_BLOCK_QUOTE_SINGLE]	=	sy_token_pass,
		[TOKEN_BLOCK_QUOTE_DOUBLE]	=	sy_token_pass,
		[TOKEN_TEXT]			=	sy_token_pass,
		[TOKEN_PIPE] 			=	sy_token_pipe,
		[TOKEN_LESS_THAN] 		=	sy_token_redir,
		[TOKEN_GREATER_THAN]	=	sy_token_redir,
		[TOKEN_APPEND] 			=	sy_token_redir,
		[TOKEN_HEREDOC]			=	sy_token_redir,
		[TOKEN_ALLOC] 			= 	sy_token_pass,
		[TOKEN_BLOCK_DOLLAR] 	=	sy_token_variable,
		[TOKEN_ERROR]			=	sy_token_err,
	};

	while (tokens)
	{
		if (!(*funcs[tokens->token.kind])(tokens))
		{
			return tokens;
		}
		tokens = tokens->next;
	}

	return (NULL);
}
