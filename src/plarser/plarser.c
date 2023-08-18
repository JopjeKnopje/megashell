/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   plarser.c                                         :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <marvin@42.fr>                       +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/08/16 12:26:52 by jboeve        #+#    #+#                 */
/*   Updated: 2023/08/18 23:33:30 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "plarser.h"
#include "test_utils.h"
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
	print_tokens(tokens);
	// TODO expansion before syntax check.
	sy_main(tokens);
	lx_lst_free(tokens);
}
