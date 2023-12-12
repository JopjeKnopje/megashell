/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   parser.c                                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/08/20 00:08:00 by joppe         #+#    #+#                 */
/*   Updated: 2023/12/12 16:47:55 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "libft.h"
#include "utils.h"
#include "plarser.h"
#include "test_utils.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int	pr_parse_text(t_cmd_frame *frame, t_tok_list *tokens)
{
	size_t	i;
	char	*s_alloc;

	i = 0;
	if (!frame->argv)
		frame->argv = ft_calloc(1, sizeof(char *));
	if (!frame->argv)
		return (0);
	while (frame->argv[i])
		i++;
	if (tokens->token.kind == TOKEN_ALLOC)
		s_alloc = tokens->token.content;
	else
		s_alloc = sized_strdup(tokens->token.content, \
					tokens->token.content_len);
	if (!s_alloc)
		return (free_2d(frame->argv), 0);
	frame->argv = str_arr_append(frame->argv, s_alloc);
	if (!frame->argv)
		return (free(s_alloc), 0);
	return (1);
}

static int	pr_parse_redirect(t_cmd_frame *frame, t_tok_list *tokens)
{
	const t_token_kind	k = tokens->token.kind;
	const t_token		*next = &tokens->next->token;

	if (k == TOKEN_APPEND || k == TOKEN_GREATER_THAN)
	{
		frame->is_append = (k == TOKEN_APPEND);
		frame->outfile = sized_strdup(next->content, next->content_len);
		if (!frame->outfile)
			printf("sized_strdup failure\n");
	}
	else if (k == TOKEN_LESS_THAN)
	{
		frame->infile = sized_strdup(next->content, next->content_len);
		if (!frame->infile)
			printf("sized_strdup failure\n");
	}
	else if (k == TOKEN_HEREDOC)
	{
		frame->heredoc_delim = sized_strdup(next->content, next->content_len);
		if (!frame->heredoc_delim)
			printf("sized_strdup failure\n");
	}
	return (1);
}

static bool	pr_is_redirect(t_token_kind k)
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

static t_cmd_list	*pr_list_add_cmd(t_cmd_list **cmd_list, t_cmd_frame t)
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

t_cmd_list	*pr_main(t_tok_list *tokens)
{
	t_cmd_list	*cmds = NULL;
	t_cmd_frame	frame;
	ft_bzero(&frame, sizeof(t_cmd_frame));

	if (!pr_joiner(tokens))
		return (NULL);
	while (tokens)
	{
		if (!tokens->prev || tokens->token.kind == TOKEN_PIPE)
		{
			if (tokens->token.kind == TOKEN_PIPE)
				pr_list_add_cmd(&cmds, frame);
			ft_bzero(&frame, sizeof(t_cmd_frame));
		}
		if (tokens->token.kind == TOKEN_TEXT || tokens->token.kind == TOKEN_ALLOC)
		{
			if (!pr_parse_text(&frame, tokens))
			{
				pr_lst_free(cmds);
				return (NULL);
			}
		}
		else if (pr_is_redirect(tokens->token.kind))
		{
			if (!pr_parse_redirect(&frame, tokens))
			{
				pr_lst_free(cmds);
				return (NULL);
			}
			tokens = tokens->next;
		}
		if (!tokens->next && !pr_list_add_cmd(&cmds, frame))
		{
			pr_lst_free(cmds);
			return (NULL);
		}
		tokens = tokens->next;
	}
	return (cmds);
}
