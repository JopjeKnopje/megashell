/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   plarser.c                                         :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <marvin@42.fr>                       +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/08/16 12:26:52 by jboeve        #+#    #+#                 */
/*   Updated: 2023/08/20 00:22:01 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "plarser.h"
#include "test_utils.h"
#include <stdio.h>
#include <stdlib.h>

t_cf_list *plarser_main(char *line)
{
	t_tok_list *tokens;

	tokens = lx_main(line);
	if (!tokens)
	{
		printf("lexer malloc failure\n");
		return (NULL);
	}
	// TODO expansion before syntax check.
	t_tok_list *err = sy_main(tokens);
	if (err)
	{
		printf("syntax error at token '%.*s'\n", err->token.content_len, err->token.content);
		lx_lst_free(tokens);
		return (NULL);
	}
	t_cf_list *cmds = pr_main(tokens);
	lx_lst_free(tokens);
	return (cmds);
}
