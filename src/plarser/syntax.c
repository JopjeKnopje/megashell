/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   syntax.c                                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/08/18 21:20:04 by joppe         #+#    #+#                 */
/*   Updated: 2023/08/18 23:32:22 by joppe         ########   odam.nl         */
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



static t_tok_list *sy_foward_list(t_tok_list *tokens, uint32_t skip)
{
	while (tokens && skip)
	{
		skip--;
		tokens = tokens->next;
	}
	return tokens;
}


typedef bool	(*t_syntax_func) (t_tok_list *t_cur);

t_syntax_error sy_main(t_tok_list *tokens)
{
	
	const t_syntax_func	funcs[TOKEN_COUNT] = {
		NULL,
		[TOKEN_QUOTE_SINGLE] = sy_token_quote,
		[TOKEN_QUOTE_DOUBLE] = sy_token_quote,
		[TOKEN_DOLLAR] = sy_token_variable,
		[TOKEN_PIPE] = sy_token_pipe,
		[TOKEN_LESS_THAN] = sy_token_redir,
		[TOKEN_GREATER_THAN] = sy_token_redir,
		[TOKEN_TEXT] = NULL,
		NULL,
	};

	uint32_t skip = 1;
	while (tokens)
	{
		t_syntax_func f = funcs[tokens->token.kind];
		if (!*f)
		{
			printf("syntax check not implemented yet\n");
		}
		else
		{
			bool ret_val = (*f)(tokens);
			if (ret_val)
			{
				printf("syntax error\n");
				print_token(tokens->token);
			}
		}
		tokens = sy_foward_list(tokens, skip);
	}

	return (lx_token_set(TOKEN_UNKNOWN, NULL, 0));
}
