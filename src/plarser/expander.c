/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   expander.c                                        :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/29 23:35:50 by joppe         #+#    #+#                 */
/*   Updated: 2023/11/01 11:02:05 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "plarser.h"
#include "test_utils.h"
#include <stdio.h>

static char *ex_find_var(char **envp, char *name, size_t len)
{
	size_t	i = 0;
	char	*var;

	if (*name == '$')
	{
		name++;
		len--;
	}

	while (envp[i])
	{
		if (!ft_strncmp(envp[i], name, len))
		{
			var = ft_strchr(envp[i], '=');
			if (*var == '=')
				var++;
			return (var);
		}
		i++;
	}
	return (NULL);
}

static char *ex_skip_var(char *s)
{
	uint32_t	i;

	i = 0;
	if (!lx_is_varchar(s[i]) || ft_isdigit(s[i]))
		return (s + i);
	while (s[i] && !lx_is_metachar(s[i]))
	{
		if (!lx_is_varchar(s[i]) && !ft_isdigit(s[i]))
			return (s + i);
		i++;
	}
	return (s + i);
}

static void ex_quote_to_var(t_token *t)
{
	if (t->content[0] == '$')
	{
		t->content++;
		// TODO strrchr to "
		t->content_len -= 2;
		t->kind = TOKEN_DOLLAR;
	}
}
static void ex_step_into_quote(t_token *t)
{
	if (t->content[0] == '"')
	{
		t->content++;
		t->content_len -= 2;
		t->kind = TOKEN_UNKNOWN;
	}

}

static void ex_expand_quote(t_token *t)
{
	// TODO	iterate over quote content, and insert anything thats
	//		not a var into the tokens list as text.
	// 		expand the variables

	size_t i = 0;
	t_tok_list *sub_list = NULL;


	ex_step_into_quote(t);
	sub_list = lx_main(t->content, t->content_len);

	printf("expanding tokens in quote\n");
	print_tokens(sub_list);
	printf("done expanding\n");

	// ex_quote_to_var(t);
}

static void ex_expand_var(char **envp, t_token *t)
{
	char	*exp;

	exp = ex_find_var(envp, t->content, t->content_len);
	if (!exp)
	{
		printf("[%s] not found, skipping..\n", exp);
		t->content = ex_skip_var(t->content);
		return;
	}

	t->content = exp;
	t->content_len = ft_strlen(exp);
	t->kind = TOKEN_TEXT;
}

bool ex_main(char **envp, t_tok_list *tokens)
{
	t_token	*t;
	
	while (tokens)
	{
		t = &tokens->token;
		if (t->kind == TOKEN_QUOTE_DOUBLE)
		{
			ex_expand_quote(t);
		}
		if (t->kind == TOKEN_DOLLAR)
		{
			ex_expand_var(envp, t);
		}
		tokens = tokens->next;
	}

	return (true);
}
