/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   parser_utils.c                                    :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <jboeve@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/12/12 16:48:09 by jboeve        #+#    #+#                 */
/*   Updated: 2023/12/23 00:14:13 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "plarser.h"
#include "utils.h"
#include "execute.h"

bool	pr_is_redirect(t_token_kind k)
{
	const bool	is_redir[TOKEN_COUNT] = {
	[TOKEN_UNUSED] = NULL,
	[TOKEN_QUOTE_SINGLE] = false,
	[TOKEN_QUOTE_DOUBLE] = false,
	[TOKEN_TEXT] = false,
	[TOKEN_PIPE] = false,
	[TOKEN_LESS_THAN] = true,
	[TOKEN_GREATER_THAN] = true,
	[TOKEN_APPEND] = true,
	[TOKEN_HEREDOC] = true,
	[TOKEN_BLOCK_DOLLAR] = false,
	[TOKEN_ERROR] = NULL,
	};

	return (is_redir[k]);
}

void	pr_parse_tokenless(t_cmd_frame *frame, const t_token *next)
{
	if (frame->heredoc_delim)
	{
		free(frame->heredoc_delim);
		frame->heredoc_delim = NULL;
	}
	if (frame->infile)
		free(frame->infile);
	frame->infile = sized_strdup(next->content, next->content_len);
	if (!frame->infile)
		print_error("sized_strdup failure\n");
}
