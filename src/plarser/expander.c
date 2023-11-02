/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   expander.c                                        :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/29 23:35:50 by joppe         #+#    #+#                 */
/*   Updated: 2023/11/02 20:49:45 by jboeve        ########   odam.nl         */
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

// TODO Try to use lx_tokenize_dollar
t_token ex_tokenize_dollar(char *s)
{
	uint32_t		i;
	t_token_kind	k;

	i = 1;
	// Nasty hack
	while (s[i] == '?' && s[i] && !lx_is_metachar(s[i]))
	{
		i++;
	}
	if (i == 2)
		return (lx_token_set(TOKEN_DOLLAR, s, i));
	i = 1;
	k = TOKEN_DOLLAR;
	if ((!lx_is_varchar(s[i]) || ft_isdigit(s[i])))
		k = TOKEN_ERROR;
	while (s[i] && !lx_is_metachar(s[i]))
	{
		if (!lx_is_varchar(s[i]) && !ft_isdigit(s[i]))
			k = TOKEN_ERROR;
		i++;
	}
	return (lx_token_set(k, s, i));
}


static t_token ex_alloc_expansion(t_token *tok_main, t_token *tok_var)
{
	// Calculate size of new string
	// calloc
	// copy tok_main join tok_var
	// set type to TOKEN_TEXT

	size_t len = tok_main->content_len + tok_var->content_len;
	char *s = ft_calloc(len + 1, sizeof(char));

	ft_memcpy(s, tok_main->content, tok_main->content_len);
	ft_memcpy(s + tok_main->content_len, tok_var->content, tok_var->content_len);

	t_token t;

	t.content = s;
	t.content_len = ft_strlen(s);
	t.kind = TOKEN_ALLOC;
	return t;
}

char	*strjoin_len(char *s_base, char *s_append, size_t len_append)
{
	int		i;
	char	*s_new;
	size_t	len_base;

	if (!s_base)
		s_base = ft_calloc(1, sizeof(char));
	len_base = ft_strlen(s_base);
	s_new = malloc(len_base + len_append + 1);
	if (!s_new)
		return (free(s_base), (NULL));
	i = 0;
	while (s_base[i])
	{
		s_new[i] = s_base[i];
		i++;
	}
	i = 0;
	while (i < len_append && s_append[i])
	{
		s_new[len_base + i] = s_append[i];
		i++;
	}
	printf("added [%.*s] to [%s]\n", (int) len_append, s_append, s_base);
	free(s_base);
	s_new[len_base + len_append] = 0;
	return (s_new);
}

static void ex_expand_quote(char **envp, t_token *tok_quote)
{
	t_token t;
	size_t i = 0;

	ex_step_into_quote(tok_quote);
	char *s = sized_strdup(tok_quote->content, tok_quote->content_len);

	char *s_exp = NULL;


	while (i < tok_quote->content_len && s[i])
	{
		if (s[i] == '$')
		{
			// $SHELL
			t = ex_tokenize_dollar(s + i);
			size_t len_old = t.content_len;
			if (t.kind == TOKEN_ERROR)
			{
				UNIMPLEMENTED("ex_tokenize_dollar failed");
			}
			t.content = ex_find_var(envp, t.content, t.content_len);
			t.content_len = ft_strlen(t.content);

			s_exp = strjoin_len(s_exp, t.content, t.content_len);
			i += len_old;
		}
		else if (s[i])
		{
			char *next_dollar = ft_strchr(&s[i + 1], '$');
			size_t distance;
			if (!next_dollar)
			{
				distance = ft_strlen(s + i);
			}
			else
			{
				distance = (s + i) - next_dollar;
			}

			printf("distance [%ld]\n", distance);
			s_exp = strjoin_len(s_exp, &s[i], distance);
			i += distance;
		}
		// i++;
	}

	// tok_quote->kind = TOKEN_ALLOC;
	// tok_quote->content = content;
	// tok_quote->content_len = ft_strlen(content);
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
