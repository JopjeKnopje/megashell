/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   plarser.c                                         :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <marvin@42.fr>                       +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/08/16 12:26:52 by jboeve        #+#    #+#                 */
/*   Updated: 2023/08/16 14:54:01 by jboeve        ########   odam.nl         */
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
	}

	pr_main(tokens);

}
