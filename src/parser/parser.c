/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   parser.c                                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/08/12 23:18:28 by joppe         #+#    #+#                 */
/*   Updated: 2023/08/15 17:59:59 by jboeve        ########   odam.nl         */
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

static void print_tokens(t_token_list *lst)
{
	while (lst)
	{
		t_token t = lst->token;
		printf("\x1b[36;49m");
		printf("token_kind \t\t[%s]\ntoken_content\t\t[%.*s]\ntoken_content_len\t[%d]\n", TOKEN_NAMES[t.kind], t.content_len, t.content, t.content_len);
		if (lst->next)
			printf("\n");
		printf("\x1b[0m");
		lst = lst->next;
	}
}

static void cf_init_argv(t_command_frame *frame)
{
	

}

static uint32_t pr_count_argv(t_token_list *tok_list)
{
	uint32_t count = 0;
	while (tok_list && tok_list->token.kind == TOKEN_TEXT)
	{
		tok_list = tok_list->next;
		count++;
	}
	return count;
}

char	*sized_strdup(const char *s, size_t len)
{
	char	*s_d;

	s_d = ft_calloc(sizeof(char), len + 1);
	if (!s_d)
		return (NULL);
	return (ft_memcpy(s_d, s, len + 1));
}


void pr_main(t_token_list *tok_list)
{
	t_token_list *it = tok_list;
	t_command_frame frame;

	print_tokens(tok_list);

	while (it)
	{
		if (it->token.kind == TOKEN_TEXT)
		{
			uint32_t count = pr_count_argv(it);
			frame.argv = ft_calloc(sizeof(char *), count + 1);
			
			for (size_t i = 0; i < count; i++)
			{
				frame.argv[i] = sized_strdup(it->token.content, it->token.content_len);
				it = it->next;
			}
			continue;
		}
		
		

		it = it->next;
	}
}
