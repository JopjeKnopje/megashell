/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   test_expander.c                                   :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/06 19:51:49 by joppe         #+#    #+#                 */
/*   Updated: 2023/11/29 18:27:02 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/logging.h>
#include <stdio.h>
#include <stdlib.h>
#include "plarser.h"

#define TEST_ASSERT_PARAMS(params) \
	do { \
	size_t size_res = ft_strlen(params.result); \
	size_t size_exp = ft_strlen(params.expected); \
	cr_expect(size_res == size_exp && !test_strncmp(params.result, params.expected, size_res, size_exp), "input [%.*s]\nresult [%ld]\t\texpected [%ld]\nresult [%s]\t\texpected [%s]\n", (int) params.input.content_len, params.input.content, size_res, size_exp, params.result, params.expected); \
	} while (0)

typedef struct s_test_params {
	t_token input;
	char *result;
	char *expected;
} t_test_params;



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

char *ex_expand_var_block(char **envp, t_token *t);

Test(expander, basic_variable)
{
	t_test_params params = {
		.input = {
			TOKEN_BLOCK_DOLLAR,
			.content_len = 4,
			0,
			.content = "$VAR",
		},
		.expected = "value",
	};

	char *envp[] = {"VAR=value", NULL};
	params.result = ex_expand_var_block(envp, &params.input);
	TEST_ASSERT_PARAMS(params);
	free(params.result);
}

Test(expander, basic_variable_underscore)
{
	t_test_params params = {
		.input = {
			TOKEN_BLOCK_DOLLAR,
			.content_len = 5,
			0,
			.content = "$_VAR",
		},
		.expected = "_value",
	};
	char *envp[] = {"_VAR=_value", NULL};

	params.result = ex_expand_var_block(envp, &params.input);
	TEST_ASSERT_PARAMS(params);
	free(params.result);
}

Test(expander, basic_variable_multiple)
{
	t_test_params params = {
		.input = {
			TOKEN_BLOCK_DOLLAR,
			.content_len = 10,
			0,
			.content = "$VAR1$VAR2",
		},
		.expected = "value1value2",
	};
	char *envp[] = {"VAR1=value1", "VAR2=value2", NULL};

	params.result = ex_expand_var_block(envp, &params.input);
	TEST_ASSERT_PARAMS(params);
	free(params.result);
}

// Test(expander, basic_variable_question_mark)
// {
// 	t_test_params params = {
// 		.input = {
// 			TOKEN_BLOCK_DOLLAR,
// 			.content_len = 2,
// 			.content = "$?",
// 		},
// 		.expected = "69",
// 	};
// 	char *envp[] = {"?=123", NULL};
//
// 	params.result = ex_expand_var_block(envp, &params.input);
// 	TEST_ASSERT_PARAMS(params);
// 	free(params.result);
// }

// Test(expander, basic_variable_unfinished)
// {
// 	t_test_params params = {
// 		.input = {
// 			TOKEN_BLOCK_DOLLAR,
// 			.content_len = 3,
// 			.content = "$?$",
// 		},
// 		.expected = "69$",
// 	};
// 	char *envp[] = {"?=123", NULL};
//
// 	params.result = ex_expand_var_block(envp, &params.input);
// 	TEST_ASSERT_PARAMS(params);
// 	free(params.result);
// }


Test(expander, text_variable_unfinished)
{
	t_test_params params = {
		.input = {
			TOKEN_BLOCK_DOLLAR,
			.content_len = 5,
			0,
			.content = "$var$",
		},
		.expected = "123$",
	};
	char *envp[] = {"var=123", NULL};

	params.result = ex_expand_var_block(envp, &params.input);
	TEST_ASSERT_PARAMS(params);
	free(params.result);
}

