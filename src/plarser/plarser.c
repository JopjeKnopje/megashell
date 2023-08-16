/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   plarser.c                                         :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <marvin@42.fr>                       +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/08/16 12:26:52 by jboeve        #+#    #+#                 */
/*   Updated: 2023/08/16 13:13:05 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "plarser.h"
#include <stdio.h>

void plarser_main(char *line)
{
	t_tok_list *tokens;

	tokens = lx_main(line);

	pr_main(tokens);

}
