/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   test_expander.c                                   :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/06 19:51:49 by joppe         #+#    #+#                 */
/*   Updated: 2023/11/06 20:38:42 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/logging.h>
#include <stdio.h>
#include "plarser.h"

#define TEST_ASSERT_PARAMS(param) \
	do { \
	size_t size_res = ft_strlen(params.result); \
	size_t size_exp = ft_strlen(params.expected); \
	cr_expect(size_res == size_exp && !test_strncmp(params.result, params.expected, size_res, size_exp), "result [%ld]\t\texpected [%ld]\nresult [%s]\t\texpected [%s]\n" , size_res, size_exp, params.result, params.expected); \
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

char *ex_expand_var(char **envp, t_token *t);

Test(expander, basic_variable)
{
	t_test_params params = {
		.input = {
			TOKEN_BLOCK_DOLLAR,
			.content_len = 4,
			.content = "$VAR",
		},
		.expected = "value",
	};

	char *envp[] = {"VAR=value", NULL};
	params.result = ex_expand_var(envp, &params.input);
	TEST_ASSERT_PARAMS(params);
}

Test(expander, basic_variable_underscore)
{
	t_test_params params = {
		.input = {
			TOKEN_BLOCK_DOLLAR,
			.content_len = 5,
			.content = "$_VAR",
		},
		.expected = "_value",
	};
	char *envp[] = {"_VAR=_value", NULL};

	params.result = ex_expand_var(envp, &params.input);
	TEST_ASSERT_PARAMS(params);
}

Test(expander, basic_variable_multiple)
{
	t_test_params params = {
		.input = {
			TOKEN_BLOCK_DOLLAR,
			.content_len = 10,
			.content = "$VAR1$VAR2",
		},
		.expected = "value1value2",
	};
	char *envp[] = {"VAR1=value1", "VAR2=value2", NULL};

	params.result = ex_expand_var(envp, &params.input);
	TEST_ASSERT_PARAMS(params);
}

Test(expander, basic_variable_question_mark)
{
	t_test_params params = {
		.input = {
			TOKEN_BLOCK_DOLLAR,
			.content_len = 2,
			.content = "$?",
		},
		.expected = "123",
	};
	char *envp[] = {"?=123", NULL};

	params.result = ex_expand_var(envp, &params.input);
	TEST_ASSERT_PARAMS(params);
}
