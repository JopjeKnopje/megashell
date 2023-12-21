/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   parser.c                                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/08/20 00:08:00 by joppe         #+#    #+#                 */
/*   Updated: 2023/12/21 17:09:25 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "test_utils.h"

#include "execute.h"
#include "libft.h"
#include "utils.h"
#include "plarser.h"
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
		if (frame->heredoc_delim)
			free(frame->heredoc_delim);
		frame->heredoc_delim = sized_strdup(next->content, next->content_len);
		if (!frame->heredoc_delim)
			printf("sized_strdup failure\n");
	}
	return (1);
}

static t_cmd_list	*pr_list_add_cmd(t_cmd_list **cmd_list, t_cmd_frame frame)
{
	t_cmd_list	*node;

	if (!cmd_list)
	{
		*cmd_list = pr_lstnew(frame);
		if (!cmd_list)
			return (NULL);
	}
	else
	{
		node = pr_lstnew(frame);
		if (!node)
			return (NULL);
		pr_lstadd_back(cmd_list, node);
	}
	return (*cmd_list);
}

static int	pr_iterate(t_tok_list **tl, t_cmd_list **cmds, t_cmd_frame *frame)
{
	if (!(*tl)->prev || (*tl)->token.kind == TOKEN_PIPE)
	{
		if ((*tl)->token.kind == TOKEN_PIPE)
			pr_list_add_cmd(cmds, *frame);
		ft_bzero(frame, sizeof(t_cmd_frame));
	}
	if ((*tl)->token.kind == TOKEN_TEXT || (*tl)->token.kind == TOKEN_ALLOC)
	{
		if (!pr_parse_text(frame, *tl))
			return (0);
	}
	else if (pr_is_redirect((*tl)->token.kind))
	{
		if (!pr_parse_redirect(frame, (*tl)))
			return (0);
		*tl = (*tl)->next;
	}
	if (!(*tl)->next && !pr_list_add_cmd(cmds, *frame))
		return (0);
	return (1);
}

t_cmd_list	*pr_main(t_tok_list *tokens)
{
	t_cmd_list	*cmds;
	t_cmd_frame	frame;

	cmds = NULL;
	ft_bzero(&frame, sizeof(t_cmd_frame));
	if (!pr_joiner(tokens))
		return (NULL);
	print_tokens(tokens);
	printf("\n\n\n\n");
	while (tokens)
	{
		if (!pr_iterate(&tokens, &cmds, &frame))
		{
			pr_lst_free(cmds);
			return (NULL);
		}
		tokens = tokens->next;
	}
	return (cmds);
}
