/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   parser.c                                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/08/12 23:18:28 by joppe         #+#    #+#                 */
/*   Updated: 2023/08/14 18:22:18 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


/** The parser spits out a linked of all the commands it should run
  * With their corresponding attrs such as, in/out file, args, 
  *
  */

#include "libft.h"
#include "lexer.h"
#include "test_utils.h"
#include "parser.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

static t_cf_list *pr_list_add_token(t_cf_list **cf_list, t_command_frame frame)
{
	t_cf_list	*node;

	if (!cf_list)
	{
		*cf_list = pr_lstnew(frame);
		if (!cf_list)
			return (NULL);
	}
	else
	{
		node = pr_lstnew(frame);
		if (!node)
			return (NULL);
		pr_lstadd_back(cf_list, node);
	}
	return (*cf_list);
}

void pr_main(t_token_list *tok_list)
{
	t_token_list *tmp = tok_list;

	t_command_frame frame;

	while (tmp)
	{
		t_token *t = &(tmp->content);

		// is input redir?
		// is text/command
		// the rest are all args up until a meta char
		// if meta char check redir or pipe

		printf("\x1b[36;49m");
		printf("token_kind %s | token_content [%.*s] | token_content_len [%d]\n", TOKEN_NAMES[t->kind], t->content_len, t->content, t->content_len);
		printf("\x1b[0m");


		tmp = tmp->next;
	}


	frame.io = 0;

	frame.io = IO_APPEND | IO_INFILE;

	print_bits(1, &frame.io);
}

int main(int argc, char *argv[])
{


	// uint8_t io = IO_STDOUT | IO_OUTFILE | IO_PIPE | IO_APPEND | IO_STDIN | IO_INFILE;
	uint8_t io = 0;

	// io = IO_INFILE | IO_STDOUT;
	io = IO_INFILE;

	print_bits(1, &io);

	uint8_t check = (IO_STDOUT | IO_INFILE);
	print_bits(1, &check);

	if (io & check)
		printf("yup\n");

	return 0;
}
