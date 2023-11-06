/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   expander.c                                        :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/29 23:35:50 by joppe         #+#    #+#                 */
/*   Updated: 2023/11/06 23:33:08 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include "libft.h"
#include "plarser.h"
#include "test_utils.h"
#include "utils.h"
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

static char *ex_find_var(char **envp, char *name, size_t len)
{
	size_t	i = 0;
	char	*var;

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

static void ex_step_into_quote(t_token *t)
{
	if (t->content[0] == '"')
	{
		t->content++;
		t->content_len -= 2;
		t->kind = TOKEN_UNKNOWN;
	}
}

static char *ex_str_append(char *s_base, char *s_append, size_t append_size)
{
	char	*s_new;
	size_t	base_size;

	if (!s_base)
		s_base = ft_calloc(1, sizeof(char));
	if (!s_base)
		return (NULL);
	base_size = ft_strlen(s_base);
	s_new = ft_calloc(base_size + append_size + 1, sizeof(char));
	if (!s_new)
		return (NULL);
	ft_memcpy(s_new, s_base, base_size);
	ft_memcpy(s_new + base_size, s_append, append_size);
	free(s_base);
	return (s_new);
}

void ex_expand_quote_block(char **envp, t_token *t)
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
			// we totally ignore the fact that the token is an TOKEN_DOLLAR.
			// we just check if its an TOKEN_ERROR
			t_token var = lx_tokenize_dollar_block(s);
			print_token(var);
			char *exp = ex_find_var(envp, var.content, var.content_len);
			if (!exp)
			{
				exp = ft_strdup("");
				if (!exp)
					UNIMPLEMENTED("Handle malloc failure");
			}
			s_exp = ex_str_append(s_exp, exp, ft_strlen(exp));
			if (!s_exp)
				UNIMPLEMENTED("Handle malloc failure");
			s += var.content_len;
		}
		else
		{
			char *var_next = ft_strchr(s, '$');
			size_t len = var_next - s;
			if (!var_next)
				len = ft_strlen(s);
			s_exp = ex_str_append(s_exp, s, len);
			if (!s_exp)
				UNIMPLEMENTED("Handle malloc failure");
			s += len;
	 	}
	}

	t->content = s_exp;
	t->content_len = ft_strlen(s_exp);
	t->kind = TOKEN_ALLOC;
	printf("expanded string [%s]\n", s_exp);
}


static size_t ex_var_len(char *s)
{
	size_t i = 0;

	while (s[i] && lx_is_valid_var_char(s[i], i == 0))
	{
		i++;
	}
	return i;
}

// iterate over var_block
// single out each variable
// expand each single variable
// append expanded variable to string
// set token with expanded string and set t_token_kind to TOKEN_TEXT
char *ex_expand_var_block(char **envp, t_token *t)
{
	char	*s_exp;
	char	*var;
	size_t	len;
	size_t	i;

	i = 0;
	s_exp = NULL;
	while (i < t->content_len)
	{
		if (t->content[i] == '$')
		{
			i++;
			len = ex_var_len(t->content + i);
			var = ex_find_var(envp, t->content + i, len);
			if (!var)
				var = "";
			s_exp = ex_str_append(s_exp, var, ft_strlen(var));
			if (!s_exp)
				UNIMPLEMENTED("Handle malloc failure");
			i += len;
			continue;
		}
		i++;
	}
	t->content = s_exp;
	t->content_len = ft_strlen(s_exp);
	t->kind = TOKEN_ALLOC;
	return s_exp;
}


bool ex_main(char **envp, t_tok_list *tokens)
{
	t_token	*t;

	while (tokens)
	{
		t = &tokens->token;
		if (t->kind == TOKEN_BLOCK_QUOTE_DOUBLE)
		{
			ex_expand_quote_block(envp, t);
		}
		if (t->kind == TOKEN_BLOCK_DOLLAR)
		{
			ex_expand_var_block(envp, t);
		}
		tokens = tokens->next;
	}

	return (true);
}
