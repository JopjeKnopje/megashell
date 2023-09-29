/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   expander.c                                        :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/09/22 22:22:44 by joppe         #+#    #+#                 */
/*   Updated: 2023/09/29 13:07:15 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "plarser.h"



t_tok_list *ex_main(char **envp, t_tok_list *tokens)
{
	t_tok_list *token = tokens;

	while (token)
	{
		if (token->token.kind == TOKEN_VARIABLE)
		{

		}
			
		token = token->next;
	}


	// return (NULL);
	return tokens;
}
