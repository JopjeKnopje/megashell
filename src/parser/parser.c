/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   parser.c                                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/08/12 23:18:28 by joppe         #+#    #+#                 */
/*   Updated: 2023/08/15 19:23:15 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


/** The parser spits out a linked of all the commands it should run
  * With their corresponding attrs such as, in/out file, args, 
  *
  */

#include "test_utils.h"


#include "libft.h"
#include "lexer.h"
#include "utils.h"
#include "parser.h"
#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

static void print_2d_arr(char **s, char *name)
{
	size_t i = 0;
	while (s[i])
	{
		printf("%s[%ld] -> [%s]\n", name, i, s[i]);
		i++;
	}

}

static void print_cf_list(t_cf_list *list)
{
	char **argv;
	char *infile;
	char *outfile;
	uint8_t io_flags;

	printf("\n");
	printf("\x1b[35;49m");
	while (list)
	{
		argv = list->content.argv;
		infile = list->content.infile;
		outfile = list->content.outfile;
		io_flags = list->content.io_flags;

		if (argv)
			print_2d_arr(argv, "argv");
		if (infile)
			printf("infile -> [%s]\n", infile);
		if (outfile)
			printf("outfile -> [%s]\n", outfile);
		if (io_flags)
			printf("io_flags -> [%x]\n", io_flags);
		list = list->next;
	}
	printf("\x1b[0m");
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

static void cf_list_free_node(t_cf_list *node)
{
	str_free_2d(node->content.argv);
}

void pr_main(t_token_list *tok_list)
{
	t_token_list *it = tok_list;
	t_cf_list *cf_list = NULL;
	t_command_frame frame;

	ft_bzero(&frame, sizeof(t_command_frame));

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

				if (!frame.argv[i])
				{
					assert(0 && "MALLOC FAILURE");
				}
				it = it->next;
			}
			pr_list_add_token(&cf_list, frame);
			continue;
		}
		it = it->next;
	}
	print_cf_list(cf_list);
	pr_lst_free(cf_list, cf_list_free_node);
}
