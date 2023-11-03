/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   test_tokenizer_dollar.c                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <jboeve@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/03 16:05:40 by jboeve        #+#    #+#                 */
/*   Updated: 2023/11/03 19:45:16 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "libft.h"
#include "plarser.h"


typedef enum e_token_kind {
	TOKEN_UNKNOWN 		= 0,
	TOKEN_QUOTE_SINGLE 	= 1, // '[content]'
	TOKEN_QUOTE_DOUBLE 	= 2, // "[content]"
	TOKEN_DOLLAR 		= 3, // $
	TOKEN_PIPE 			= 4, // |
	TOKEN_LESS_THAN 	= 5, // <
	TOKEN_GREATER_THAN 	= 6, // >
	TOKEN_APPEND 		= 7, // >>
	TOKEN_HEREDOC 		= 8, // <<
	TOKEN_TEXT 			= 9,
	TOKEN_ALLOC			= 10,
	TOKEN_ERROR 		= 11,
	TOKEN_COUNT 		= 12,
}	t_token_kind;

typedef struct s_token {
	t_token_kind	kind;
	size_t			content_len;
	char			*content;
}	t_token;



typedef struct s_testcase {
	char *input;
	t_token output;
	t_token expected;

} t_testcase;

typedef enum e_token_compare_err {
	TCE_PASSED,
	TCE_CONTENT_LEN,
	TCE_CONTENT,
	TCE_KIND,
	TCE_COUNT,
} t_token_compare_err;

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
	"TOKEN_ALLOC",
	"TOKEN_ERROR",
	"TOKEN_COUNT",
};



void test_log(t_token_compare_err err, t_testcase test)
{
	// TODO Print the error value
	if (!err)
	{
		printf("[PASSED] ");
		printf("\tINPUT: [%s] ", test.input);
		printf("\t[%s]\ntoken_content\t\t[%.*s]\ntoken_content_len\t[%ld]\n", TOKEN_NAMES[test.output.kind], (int) test.output.content_len, test.output.content, test.output.content_len);
		printf("\n");
	}
	else
	{
		printf("[FAILED] ");
		printf("\tINPUT: [%s] ", test.input);
		printf("\t[%s]\ntoken_content\t\t[%.*s]\ntoken_content_len\t[%ld]\n", TOKEN_NAMES[test.expected.kind], (int) test.expected.content_len, test.expected.content, test.expected.content_len);
		printf("got\n");
		printf("\t[%s]\ntoken_content\t\t[%.*s]\ntoken_content_len\t[%ld]\n", TOKEN_NAMES[test.output.kind], (int) test.output.content_len, test.output.content, test.output.content_len);
		printf("\n");
	}
}

t_token_compare_err token_compare(t_token t1, t_token t2)
{
	if (t1.content_len != t2.content_len)
	{
		return TCE_CONTENT_LEN;	
	}
	if (t1.kind != t2.kind)
	{
		return TCE_KIND;	
	}
	if (ft_strncmp(t1.content, t2.content, t1.content_len))
	{
		return TCE_CONTENT;	
	}
	return TCE_PASSED;

}

void run_test(t_testcase test)
{
	test.output = lx_tokenize_dollar(test.input);
	t_token_compare_err err = token_compare(test.input, test.output);
	test_log(err, test);
}

int main()
{
	t_testcase case1 = {
		.input = "$",
		.output = {
			NULL,
			NULL,
			NULL,
		},
		.expected = {
			TOKEN_TEXT,
			1,
			"$",
		}
	};

	run_test(case1);


	return EXIT_SUCCESS;
}
