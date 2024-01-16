/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   test_utils.c                                      :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/08/14 18:05:42 by joppe         #+#    #+#                 */
/*   Updated: 2024/01/16 12:45:41 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "test_utils.h"
#include "plarser.h"
#include <stdint.h>
#include <stdio.h>

static const char *TOKEN_NAMES[] = {
	"TOKEN_UNUSED",
	"TOKEN_BLOCK_QUOTE_SINGLE",
	"TOKEN_BLOCK_QUOTE_DOUBLE",
	"TOKEN_BLOCK_DOLLAR",
	"TOKEN_PIPE",
	"TOKEN_LESS_THAN",
	"TOKEN_GREATER_THAN",
	"TOKEN_APPEND",
	"TOKEN_HEREDOC",
	"TOKEN_TEXT",
	"TOKEN_ALLOC",
	"TOKEN_ERROR",
	"TOKEN_COUNT",
};


const char *get_token_name(t_token_kind k)
{
	return TOKEN_NAMES[k];
}

void print_bits(size_t const size, void const * const ptr)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;
    
    for (i = size-1; i >= 0; i--) {
        for (j = 7; j >= 0; j--) {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
	printf("\n");
}

void print_token(t_token t)
{
	printf("\x1b[36;49m");
	if (t.kind == TOKEN_ALLOC)
		printf("token_kind \t\t[%s]\ntoken_content\t\t[%s]\ntoken_content_len\t[%ld]\npadding \t\t[%ld]\n", TOKEN_NAMES[t.kind], t.content, t.content_len, t.padding);
	else
		printf("token_kind \t\t[%s]\ntoken_content\t\t[%.*s]\ntoken_content_len\t[%ld]\npadding \t\t[%ld]\n", TOKEN_NAMES[t.kind], (int) t.content_len, t.content, t.content_len, t.padding);
	printf("\x1b[0m");
}

void print_tokens(t_tok_list *lst)
{
	while (lst)
	{
		print_token(lst->token);
		if (lst->next)
			printf("\n");
		lst = lst->next;
	}
}

void print_2d_arr(char **s, char *name)
{
	size_t i = 0;
	while (s[i])
	{
		if (s[i])
			printf("%s[%ld] -> [%s]\n", name, i, s[i]);
		i++;
	}
}

void print_cmds(t_cmd_list *list)
{
	char **argv;
	char *infile;
	char *outfile;
	char *heredoc_delim;

	printf("\n");
	printf("\x1b[35;49m");
	while (list)
	{
		argv = list->content.argv;
		infile = list->content.infile;
		outfile = list->content.outfile;
		heredoc_delim = list->content.heredoc_delim;

		if (argv)
			print_2d_arr(argv, "argv");
		if (infile)
			printf("infile -> [%s]\n", infile);
		if (heredoc_delim)
			printf("heredoc_delim -> [%s]\n", heredoc_delim);
		if (outfile)
			printf("outfile -> [%s]\n", outfile);
		if (list->next)
			printf("\n");
		list = list->next;
	}
	printf("\x1b[0m\n");
}
