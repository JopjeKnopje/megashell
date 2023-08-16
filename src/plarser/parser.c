/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   parser.c                                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/08/12 23:18:28 by joppe         #+#    #+#                 */
/*   Updated: 2023/08/16 13:11:33 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "test_utils.h"

#include "libft.h"
#include "utils.h"
#include "plarser.h"
#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>


uint32_t pr_count_argv(t_tok_list *tok_list, t_token_kind k)
{
	uint32_t count = 0;
	while (tok_list && tok_list->token.kind == k)
	{
		tok_list = tok_list->next;
		count++;
	}
	return count;
}

static void cf_list_free_node(t_cf_list *node)
{
	str_free_2d(node->content.argv);
}

void pr_main(t_tok_list *tokens)
{
	t_parser parser;
	ft_bzero(&parser, sizeof(t_parser));

	print_tokens(tokens);

	while (tokens)
	{
		tokens = tokens->next;
	}
	print_cf_list(parser.command_frames);
	pr_lst_free(parser.command_frames, cf_list_free_node);
}
