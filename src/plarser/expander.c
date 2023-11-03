/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   expander.c                                        :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/29 23:35:50 by joppe         #+#    #+#                 */
/*   Updated: 2023/11/03 01:06:29 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "plarser.h"
#include "test_utils.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

static char *ex_find_var(char **envp, char *name, size_t len)
{
	size_t	i = 0;
	char	*var;

	// TODO	Maybe remove this part, since we should Ideally only call this function.
	//		with or without the dollar sign.
	if (*name == '$')
	{
		name++;
		len--;
	}
	printf("looking for name [%s]\n", name);

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

// TODO Not use this func cuz its kinda shit.
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

static void ex_step_into_quote(t_token *t)
{
	if (t->content[0] == '"')
	{
		t->content++;
		t->content_len -= 2;
		t->kind = TOKEN_UNKNOWN;
	}
}

static char *ex_str_append(char *s_base, char *s_append)
{
	char	*s_new;
	size_t	base_size;
	size_t	append_size;

	if (!s_base)
		s_base = ft_calloc(1, sizeof(char));
	if (!s_base)
		return (NULL);
	base_size = ft_strlen(s_base);
	append_size = ft_strlen(s_append);;
	s_new = ft_calloc(base_size + append_size + 1, sizeof(char));
	if (!s_new)
		return (NULL);
	ft_memcpy(s_new, s_base, base_size);
	ft_memcpy(s_new + base_size, s_append, append_size);
	free(s_base);
	return (s_new);
}

static void ex_expand_quote(char **envp, t_token *t)
{
	char *s_exp = NULL;
	char *s;

	ex_step_into_quote(t);
	s = sized_strdup(t->content, t->content_len);
	if (!s)
		UNIMPLEMENTED("malloc failure check");

	while (*s)
	{
		if (*s == '$')
		{
			// tokenize the variable 
			t_token var = lx_tokenize_dollar(s);
			// expand variable
			print_token(var);
			char *exp = ex_find_var(envp, var.content, var.content_len);
			if (!exp)
				UNIMPLEMENTED("handle variable not found, (remove var from line)");

			// append expansion to s_exp
			s_exp = ex_str_append(s_exp, exp);
			// increment s by len of token_len
			s += var.content_len;
		}
		else
		{
			// find start next variable 
			// substr from current index to start of next var
			// append to s_exp
			// increment s by len of substr
			s++;
	 	}
	}
	// set `t` to our s_exp.
	printf("expanded string [%s]\n", s_exp);
}

bool ex_main(char **envp, t_tok_list *tokens)
{
	t_token	*t;

	while (tokens)
	{
		t = &tokens->token;
		if (t->kind == TOKEN_QUOTE_DOUBLE)
		{
			ex_expand_quote(envp, t);
		}
		if (t->kind == TOKEN_DOLLAR)
		{
			ex_expand_var(envp, t);
		}
		tokens = tokens->next;
	}

	return (true);
}
