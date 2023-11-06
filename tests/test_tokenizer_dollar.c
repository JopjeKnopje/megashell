/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   test_tokenizer_dollar.c                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/05 22:56:47 by joppe         #+#    #+#                 */
/*   Updated: 2023/11/06 01:07:08 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include "plarser.h"
#include "test_utils.h"

typedef struct s_test_params {
	char *input;
	t_token result;
	t_token expected;
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

void test_assert_params(t_test_params params)
{
	cr_expect(params.result.kind == params.expected.kind, "result [%s]\texpected [%s]\n", get_token_name(params.result.kind), get_token_name(params.expected.kind));
	cr_expect(params.result.content_len == params.expected.content_len, "result [%ld]\texpected[%ld]\n", params.result.content_len, params.expected.content_len);
	cr_expect(!test_strncmp(params.result.content, params.expected.content,
				params.result.content_len, params.expected.content_len), 
				"result [%.*s] \t expected [%.*s]\n",
				(int) params.result.content_len, params.result.content,
				(int) params.expected.content_len, params.expected.content);
}

Test(tokenizer_dollar, single_dollar)
{
	t_test_params params = {
		.input = "$",
		.result = {
			0,
			0,
			0,
		},
		.expected = {
			TOKEN_TEXT,
			1,
			"$",
		},
	};

	params.result = lx_tokenize_dollar(params.input);
	test_assert_params(params);
}
