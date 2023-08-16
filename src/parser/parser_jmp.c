/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   parser_jmp.c                                      :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/08/16 10:38:51 by joppe         #+#    #+#                 */
/*   Updated: 2023/08/16 11:00:18 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "lexer.h"
#include "parser.h"
#include "utils.h"

// t_tok_list *pr_parse_text(t_command_frame *frame, t_cf_list **f_list, t_tok_list **tok_list)
// {
// 	t_tok_list *tmp = *tok_list;
// 	uint32_t count = pr_count_argv(tmp, TOKEN_TEXT);
//
// 	frame->argv = ft_calloc(sizeof(char *), count + 1);
// 	for (size_t i = 0; i < count; i++)
// 	{
// 		frame->argv[i] = sized_strdup(tmp->token.content, tmp->token.content_len);
// 		tmp = tmp->next;
// 	}
// 	pr_list_add_token(f_list, *frame);
// 	return tmp;
// }

t_tok_list *pr_parse_text(t_parser *p, t_tok_list *current_token)
{

}

t_tok_list *pr_parse_token(t_parser *p, t_tok_list *current_token)
{

	t_tok_list *tmp;
	t_tok_list	*(*parse_funcs[TOKEN_COUNT]) (t_parser *p, t_tok_list *current_token) = {
		pr_parse_text,
	};

	tmp = pr_parse_text(p, current_token);




	return tmp;

}
