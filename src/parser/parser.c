/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   parser.c                                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/08/12 23:18:28 by joppe         #+#    #+#                 */
/*   Updated: 2023/08/14 10:20:25 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


/** The parser spits out a linked of all the commands it should run
  * With their corresponding attrs such as, in/out file, args, 
  *
  */

#include "libft.h"
#include "lexer.h"
#include "parser.h"
#include <stddef.h>
#include <stdio.h>

void pr_main(t_token_list *tok_list)
{
	t_token_list *tmp = tok_list;
	size_t i = 0;

	t_command_frame frame;

	while (tmp)
	{
		t_token *t = &(tmp->content);

		if (t->kind == TOKEN_TEXT)
		{

		}

		// is input redir?
		// is text/command
		// the rest are all args up until a meta char
		// if meta char check redir or pipe

		printf("\x1b[36;49m");
		printf("token_kind %s | token_content [%.*s] | token_content_len [%d]\n", TOKEN_NAMES[t->kind], t->content_len, t->content, t->content_len);
		printf("\x1b[0m");


		tmp = tmp->next;
		i++;
	}
}
