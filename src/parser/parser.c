/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   parser.c                                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/08/12 23:18:28 by joppe         #+#    #+#                 */
/*   Updated: 2023/08/15 23:52:58 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "test_utils.h"

#include "libft.h"
#include "lexer.h"
#include "utils.h"
#include "parser.h"
#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>



static uint32_t pr_count_argv(t_tok_list *tok_list, t_token_kind k)
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

t_tok_list *pr_parse_text(t_command_frame *frame, t_cf_list **frame_list, t_tok_list **tok_list)
{
	t_tok_list *tmp = *tok_list;
	uint32_t count = pr_count_argv(tmp, TOKEN_TEXT);

	frame->argv = ft_calloc(sizeof(char *), count + 1);
	for (size_t i = 0; i < count; i++)
	{
		frame->argv[i] = sized_strdup(tmp->token.content, tmp->token.content_len);
		tmp = tmp->next;
	}
	pr_list_add_token(frame_list, *frame);
	return tmp;
}

void pr_main(t_tok_list *tok_list)
{
	t_cf_list *cframe_list = NULL;
	t_tok_list *tmp = tok_list;

	t_command_frame frame;

	ft_bzero(&frame, sizeof(t_command_frame));

	print_tokens(tok_list);

	while (tmp)
	{
		if (tmp->token.kind == TOKEN_TEXT)
		{
			tmp = pr_parse_text(&frame, &cframe_list, &tmp);
			continue;
		}
		tmp = tmp->next;
	}
	print_cf_list(cframe_list);
	pr_lst_free(cframe_list, cf_list_free_node);
}
