/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   parser.c                                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/08/20 00:08:00 by joppe         #+#    #+#                 */
/*   Updated: 2023/10/18 00:33:42 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include "plarser.h"
#include "test_utils.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


t_cmd_frame pr_parse_text(t_cmd_frame frame, t_tok_list *tokens)
{
	size_t i = 0;

	if (!frame.argv)
		frame.argv = ft_calloc(1, sizeof(char *));

	while (frame.argv[i])
		i++;


	char *s = sized_strdup(tokens->token.content, tokens->token.content_len);
	if (!s)
	{
		printf("strdup_sized failed\n");
	}

	frame.argv = str_arr_append(frame.argv, s);
	if (!frame.argv)
	{
		printf("str_arr_append failed\n");
	}
	return (frame);
}

t_cmd_frame pr_parse_redirect(t_cmd_frame frame, t_tok_list *tokens)
{
	const t_token_kind k = tokens->token.kind;

	if (k == TOKEN_APPEND || k  == TOKEN_GREATER_THAN)
	{
		frame.is_append = (k == TOKEN_APPEND);
		frame.outfile = sized_strdup(tokens->next->token.content, tokens->next->token.content_len);
		if (!frame.outfile)
			printf("sized_strdup failure\n");
	}
	else if (k == TOKEN_LESS_THAN)
	{
		frame.infile = sized_strdup(tokens->next->token.content, tokens->next->token.content_len);
		if (!frame.infile)
			printf("sized_strdup failure\n");
	}
	else if (k == TOKEN_HEREDOC)
	{
		frame.heredoc_delim = sized_strdup(tokens->next->token.content, tokens->next->token.content_len);
		if (!frame.heredoc_delim)
			printf("sized_strdup failure\n");
	}

	return (frame);
}

static bool pr_is_redirect(t_token_kind k)
{
	const bool is_redir[TOKEN_COUNT] = {
		[TOKEN_UNKNOWN] 		=	NULL,
		[TOKEN_QUOTE_SINGLE]	=	false,
		[TOKEN_QUOTE_DOUBLE]	=	false,
		[TOKEN_TEXT]			=	false,
		[TOKEN_PIPE] 			=	false,
		[TOKEN_LESS_THAN] 		=	true,
		[TOKEN_GREATER_THAN]	=	true,
		[TOKEN_APPEND] 			=	true,
		[TOKEN_HEREDOC]			=	true,
		[TOKEN_DOLLAR] 			=	false,
		[TOKEN_ERROR]			=	NULL,
	};

	return is_redir[k];
}

static t_cmd_list *pr_list_add_cmd(t_cmd_list **cmd_list, t_cmd_frame t)
{
	t_cmd_list	*node;

	if (!cmd_list)
	{
		*cmd_list = pr_lstnew(t);
		if (!cmd_list)
			return (NULL);
	}
	else
	{
		node = pr_lstnew(t);
		if (!node)
			return (NULL);
		pr_lstadd_back(cmd_list, node);
	}
	return (*cmd_list);
}

t_cmd_list *pr_main(t_tok_list *tokens)
{
	t_cmd_list	*cmds = NULL;
	t_cmd_frame	frame;
	ft_bzero(&frame, sizeof(t_cmd_frame));


	// every frame can contain at max one of each redirection (in / out).
	while (tokens)
	{
		if (!tokens->prev || tokens->token.kind == TOKEN_PIPE)
		{
			if (tokens->token.kind == TOKEN_PIPE)
				pr_list_add_cmd(&cmds, frame);
			ft_bzero(&frame, sizeof(t_cmd_frame));
		}
		if (tokens->token.kind == TOKEN_TEXT)
		{
			frame = pr_parse_text(frame, tokens);
		}
		else if (pr_is_redirect(tokens->token.kind))
		{
			frame = pr_parse_redirect(frame, tokens);
			tokens = tokens->next;
		}

		if (!tokens->next)
			pr_list_add_cmd(&cmds, frame);
		tokens = tokens->next;
	}
	return (cmds);
}
