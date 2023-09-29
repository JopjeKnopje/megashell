/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   expander.c                                        :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/09/22 22:22:44 by joppe         #+#    #+#                 */
/*   Updated: 2023/09/29 13:25:43 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "plarser.h"
#include "utils.h"

t_tok_list *ex_main(char **envp, t_tok_list *tokens)
{
	t_tok_list *token = tokens;

	while (token)
	{
		if (token->token.kind == TOKEN_VARIABLE)
		{
			envp_find_var(envp, token->token.content, token->token.content_len);
		}
			
		token = token->next;
	}


	// return (NULL);
	return tokens;
}
