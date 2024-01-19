/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   test_tokenizer.c                                  :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/06 01:45:51 by joppe         #+#    #+#                 */
/*   Updated: 2024/01/19 13:45:39 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/logging.h>
#include "plarser.h"
#include "test_utils.h"

#define TEST_ASSERT_PARAMS(param) \
	do { \
	cr_expect(params.result.kind == params.expected.kind, "input \t[%s]\nresult [%s]\texpected [%s]\n", params.input, get_token_name(params.result.kind), get_token_name(params.expected.kind)); \
	cr_expect(params.result.content_len == params.expected.content_len, "input \t[%s]\nresult [%ld]\texpected[%ld]\n", params.input, params.result.content_len, params.expected.content_len); \
	cr_expect(!test_strncmp(params.result.content, params.expected.content, \
				params.result.content_len, params.expected.content_len),  \
				"input \t[%s]\nresult [%.*s] \t expected [%.*s]\n", \
				params.input, (int) params.result.content_len, params.result.content, \
				(int) params.expected.content_len, params.expected.content); \
	} while (0)

typedef struct s_test_params {
	char *input;
	t_token result;
	t_token expected;
} t_test_params;


t_token lx_next(char *s);


int	test_strncmp(const char *s1, const char *s2, size_t n1, size_t n2)
{
	size_t	i;
	size_t n = ((n1 < n2) * n2 + (!(n1 < n2)) * n1);

	i = 0;
	while (i < n && s1[i] && (s1[i] == s2[i]))
		i++;
	if (i == n)
		return (0);
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}



Test(tokenizer, single_dollar)
{
	t_test_params params = {
		.input = "$",
		.expected = {
			TOKEN_TEXT,
			1,
			0,
			"$",
		},
	};

	params.result = lx_next(params.input);
	TEST_ASSERT_PARAMS(params);
}

Test(tokenizer, var_exit_status)
{
	t_test_params params = {
		.input = "$?",
		.expected = {
			TOKEN_BLOCK_DOLLAR,
			2,
			0,
			"$?",
		},
	};

	params.result = lx_next(params.input);
	TEST_ASSERT_PARAMS(params);
}

Test(tokenizer, single_var)
{
	t_test_params params = {
		.input = "$VAR",
		.expected = {
			TOKEN_BLOCK_DOLLAR,
			4,
			0,
			"$VAR",
		},
	};

	params.result = lx_next(params.input);
	TEST_ASSERT_PARAMS(params);
}

Test(tokenizer, two_vars)
{
	t_test_params params = {
		.input = "$VAR1$VAR2",
		.expected = {
			TOKEN_BLOCK_DOLLAR,
			10,
			0,
			"$VAR1$VAR2",
		},
	};

	params.result = lx_next(params.input);
	TEST_ASSERT_PARAMS(params);
}

Test(tokenizer, variable_underscore_name)
{
	t_test_params params = {
		.input = "$_var",
		.expected = {
			TOKEN_BLOCK_DOLLAR,
			5,
			0,
			"$_var",
		},
	};

	params.result = lx_next(params.input);
	TEST_ASSERT_PARAMS(params);
}

Test(tokenizer, variable_name_underscore)
{
	t_test_params params = {
		.input = "$var_",
		.expected = {
			TOKEN_BLOCK_DOLLAR,
			5,
			0,
			"$var_",
		},
	};

	params.result = lx_next(params.input);
	TEST_ASSERT_PARAMS(params);
}

Test(tokenizer, variable_name_digit)
{
	t_test_params params = {
		.input = "$1",
		.expected = {
			TOKEN_ERROR,
			2,
			0,
			"$1",
		},
	};

	params.result = lx_next(params.input);
	TEST_ASSERT_PARAMS(params);
}

Test(tokenizer, variable_name_digit_ascii)
{
	t_test_params params = {
		.input = "$1VAR",
		.expected = {
			TOKEN_ERROR,
			5,
			0,
			"$1VAR",
		},
	};

	params.result = lx_next(params.input);
	TEST_ASSERT_PARAMS(params);
}

Test(tokenizer, variable_name_quote)
{
	t_test_params params = {
		.input = "$'",
		.expected = {
			TOKEN_ERROR,
			2,
			0,
			"$'",
		},
	};

	params.result = lx_next(params.input);
	TEST_ASSERT_PARAMS(params);
}

Test(tokenizer, variable_dollar_multiple_2)
{
	t_test_params params = {
		.input = "$$",
		.expected = {
			TOKEN_ERROR,
			2,
			0,
			"$$",
		},
	};

	params.result = lx_next(params.input);
	TEST_ASSERT_PARAMS(params);
}

Test(tokenizer, variable_dollar_multiple_3)
{
	t_test_params params = {
		.input = "$$$",
		.expected = {
			TOKEN_ERROR,
			3,
			0,
			"$$$",
		},
	};

	params.result = lx_next(params.input);
	TEST_ASSERT_PARAMS(params);
}

Test(tokenizer, variable_dollar_multiple_4)
{
	t_test_params params = {
		.input = "$$$$",
		.expected = {
			TOKEN_ERROR,
			4,
			0,
			"$$$$",
		},
	};

	params.result = lx_next(params.input);
	TEST_ASSERT_PARAMS(params);
}

Test(tokenizer, variable_dollar_multiple_5)
{
	t_test_params params = {
		.input = "$$$$$",
		.expected = {
			TOKEN_ERROR,
			5,
			0,
			"$$$$$",
		},
	};

	params.result = lx_next(params.input);
	TEST_ASSERT_PARAMS(params);
}

Test(tokenizer, single_var_unfinished)
{
	t_test_params params = {
		.input = "$VAR$",
		.expected = {
			TOKEN_BLOCK_DOLLAR,
			5,
			0,
			"$VAR$",
		},
	};

	params.result = lx_next(params.input);
	TEST_ASSERT_PARAMS(params);
}

Test(tokenizer, text_and_quote)
{
	t_test_params params = {
		.input = "a\"b\"",
		.expected = {
			TOKEN_TEXT,
			1,
			0,
			"a",
		},
	};

	params.result = lx_next(params.input);
	TEST_ASSERT_PARAMS(params);
}

Test(tokenizer, quote_and_text)
{
	t_test_params params = {
		.input = "\"b\"a",
		.expected = {
			TOKEN_QUOTE_DOUBLE,
			3,
			0,
			"\"b\"",
		},
	};

	params.result = lx_next(params.input);
	TEST_ASSERT_PARAMS(params);
}
