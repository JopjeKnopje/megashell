/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   test_utils.c                                      :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/08/14 18:05:42 by joppe         #+#    #+#                 */
/*   Updated: 2023/08/20 21:59:41 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "test_utils.h"
#include "plarser.h"
#include <stdint.h>
#include <stdio.h>

static const char *TOKEN_NAMES[] = {
	"TOKEN_UNKNOWN",
	"TOKEN_QUOTE_SINGLE",
	"TOKEN_QUOTE_DOUBLE",
	"TOKEN_DOLLAR",
	"TOKEN_PIPE",
	"TOKEN_LESS_THAN",
	"TOKEN_GREATER_THAN",
	"TOKEN_APPEND",
	"TOKEN_HEREDOC",
	"TOKEN_TEXT",
	"TOKEN_ERROR",
	"TOKEN_COUNT",
};


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
	printf("token_kind \t\t[%s]\ntoken_content\t\t[%.*s]\ntoken_content_len\t[%d]\n", TOKEN_NAMES[t.kind], t.content_len, t.content, t.content_len);
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
		printf("%s[%ld] -> [%s]\n", name, i, s[i]);
		i++;
	}
}

void print_cmds(t_cmd_list *list)
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
		if (list->next)
			printf("\n");
		list = list->next;
	}
	printf("\x1b[0m");
}
