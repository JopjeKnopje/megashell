/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   test_tokenizer_dollar.c                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <jboeve@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/03 16:05:40 by jboeve        #+#    #+#                 */
/*   Updated: 2023/11/03 19:40:25 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "libft.h"
#include "plarser.h"


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



void log(t_token_compare_err err, t_testcase test)
{
	// TODO Print the error value
	if (!err)
	{
		printf("[PASSED] ");
		printf("\t[%s]\ntoken_content\t\t[%.*s]\ntoken_content_len\t[%ld] == ", TOKEN_NAMES[test.input.kind], (int) test.input.content_len, test.input.content, test.input.content_len);
		printf("\t[%s]\ntoken_content\t\t[%.*s]\ntoken_content_len\t[%ld]\n", TOKEN_NAMES[test.output.kind], (int) test.output.content_len, test.output.content, test.output.content_len);
		printf("\n");
	}
	else
	{
		printf("[FAILED] ");
		printf("\t[%s]\ntoken_content\t\t[%.*s]\ntoken_content_len\t[%ld] != ", TOKEN_NAMES[test.input.kind], (int) test.input.content_len, test.input.content, test.input.content_len);
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
	log(err, test);
}

int main()
{

	t_testcase case1 = {
		.input = {
			TOKEN_DOLLAR,
			1,
			"$",
		}
		.output = {
			NULL,
			NULL,
			NULL,
		}
		.expected = {
			TOKEN_TEXT,
			1,
			"$",
		}
	}

	run_test(case1);


	return EXIT_SUCCESS;
}
