/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   test_expander.c                                   :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/06 19:51:49 by joppe         #+#    #+#                 */
/*   Updated: 2023/11/06 20:32:38 by joppe         ########   odam.nl         */
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
	cr_expect(size_res == size_exp, "result [%ld]\texpected[%ld]\n", size_res, size_exp); \
	cr_expect(!test_strncmp(params.result, params.expected, \
				size_res, size_exp), \
				"result [%s] \t expected [%s]\n", \
				params.result, params.expected); \
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
char *envp[] = {"VAR=value", NULL};

Test(expander, basic_variable)
{
	t_test_params params = {
		.input = {
			TOKEN_BLOCK_DOLLAR,
			.content_len = 4,
			.content = "$VAR",
		},
		.expected = "valu1e",
	};

	params.result = ex_expand_var(envp, &params.input);
	TEST_ASSERT_PARAMS(params);
}
