/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   parser.c                                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/08/20 00:08:00 by joppe         #+#    #+#                 */
/*   Updated: 2023/08/20 23:57:13 by joppe         ########   odam.nl         */
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

		if (!tokens->next)
			pr_list_add_cmd(&cmds, frame);

		tokens = tokens->next;
	}

	return (cmds);
}
