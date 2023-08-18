/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   plarser.c                                         :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <marvin@42.fr>                       +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/08/16 12:26:52 by jboeve        #+#    #+#                 */
/*   Updated: 2023/08/18 22:08:34 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "plarser.h"
#include <stdio.h>
#include <stdlib.h>

void plarser_main(char *line)
{
	t_tok_list *tokens;

	tokens = lx_main(line);
	if (!tokens)
	{
		printf("lexer malloc failure\n");
		return;
	}

	t_syntax_error err = sy_main(tokens);
	lx_lst_free(tokens);
	if (err.kind != TOKEN_UNKNOWN)
	{
		printf("syntax error near unexpected token [%.*s]\n", err.content_len, err.content);
		return;
	}

}
