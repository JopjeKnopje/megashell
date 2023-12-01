/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   parser.c                                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/08/20 00:08:00 by joppe         #+#    #+#                 */
/*   Updated: 2023/12/01 20:02:34 by joppe         ########   odam.nl         */
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
	char *s_alloc;

	if (!frame.argv)
		frame.argv = ft_calloc(1, sizeof(char *));
	if (!frame.argv)
		UNIMPLEMENTED("Handle malloc failure");

	while (frame.argv[i])
		i++;

	if (tokens->token.kind == TOKEN_ALLOC)
		s_alloc = tokens->token.content;
	else
		s_alloc = sized_strdup(tokens->token.content, tokens->token.content_len);
	if (!s_alloc)
		UNIMPLEMENTED("Handle malloc failure");
	frame.argv = str_arr_append(frame.argv, s_alloc);
	if (!frame.argv)
		UNIMPLEMENTED("Handle malloc failure");
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
		[TOKEN_UNUSED] 				=	NULL,
		[TOKEN_BLOCK_QUOTE_SINGLE]	=	false,
		[TOKEN_BLOCK_QUOTE_DOUBLE]	=	false,
		[TOKEN_TEXT]				=	false,
		[TOKEN_PIPE] 				=	false,
		[TOKEN_LESS_THAN] 			=	true,
		[TOKEN_GREATER_THAN]		=	true,
		[TOKEN_APPEND] 				=	true,
		[TOKEN_HEREDOC]				=	true,
		[TOKEN_BLOCK_DOLLAR]	 	=	false,
		[TOKEN_ERROR]				=	NULL,
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

t_tok_list *join_tokens(t_tok_list *tokens)
{
	t_tok_list *head = tokens;

	while (tokens)
	{
		t_token *t_cur	= &tokens->token;
		t_token *t_next = &tokens->next->token;

		if (!t_cur->content_len)
		{
			if (t_cur->kind == TOKEN_ALLOC)
				free(t_cur->content);
			t_cur->kind = TOKEN_UNUSED;
		}
		else if (t_next && t_cur->padding == 0)
		{
			char	*joined = sized_strjoin(t_cur->content, t_cur->content_len,
											t_next->content, t_next->content_len);
			printf("joined [%.*s] with [%.*s] == [%s]\n",
					(int) t_cur->content_len, t_cur->content,
					(int) t_next->content_len, t_next->content, joined);
			if (!t_cur->content)
				UNIMPLEMENTED("protect sized_strjoin");

			if (t_cur->kind == TOKEN_ALLOC)
				free(t_cur->content);

			if (t_next->kind == TOKEN_ALLOC)
				free(t_next->content);

			t_cur->content = joined;

			t_cur->content_len = ft_strlen(t_cur->content);
			t_cur->kind = TOKEN_ALLOC;
			t_next->kind = TOKEN_UNUSED;
		}
		tokens = tokens->next;
	}
	return (head);
}

t_cmd_list *pr_main(t_tok_list *tokens)
{
	t_cmd_list	*cmds = NULL;
	t_cmd_frame	frame;
	ft_bzero(&frame, sizeof(t_cmd_frame));

	if (!join_tokens(tokens))
		UNIMPLEMENTED("protect join_tokens");

	printf("\nafter join_tokens\n\n");
	print_tokens(tokens);


	// every frame can contain at max one of each redirection (in / out).
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
