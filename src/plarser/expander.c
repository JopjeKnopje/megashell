/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                        :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 23:35:50 by joppe             #+#    #+#             */
/*   Updated: 2023/12/13 01:15:28 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "get_next_line.h"
#include "heredoc.h"
#include "libft.h"
#include "megashell.h"
#include "plarser.h"
#include "test_utils.h"
#include "utils.h"
#include <limits.h>
#include <readline/readline.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "execute.h"

static	size_t	get_key_len(char *key)
{
	size_t	i;

	i = 0;
	while (key[i] && key[i] != '=')
	{
		i++;
	}
	return (i);
}

static char	*ex_find_var(char **envp, char *name, size_t len)
{
	size_t	i;
	char	*var;

	i = 0;
	if (!len)
		return (NULL);
	while (envp[i])
	{
		if (get_key_len(envp[i]) == len && !ft_strncmp(envp[i], name, len))
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

size_t	ex_var_len(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && lx_is_valid_var_char(s[i], i == 0))
		i++;
	return (i);
}

char	*ex_str_append(char *s_base, char *s_append, size_t append_size)
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

static size_t	ex_expand_var(char **envp, t_token *t, size_t i, char **s_exp)
{
	char	*var;
	size_t	len;
	bool	is_exit_code;

	is_exit_code = false;
	len = 0;
	if (i + 1 >= t->content_len)
		var = "$";
	else
	{
		len = ex_var_len(t->content + i + 1);
		is_exit_code = !ft_strncmp("?", t->content + i + 1, len);
		if (is_exit_code)
			var = ft_itoa(g_exit_code);
		else
			var = ex_find_var(envp, t->content + i + 1, len);
		if (!var)
			var = "";
	}
	if (!var)
		return (len);
	*s_exp = ex_str_append(*s_exp, var, ft_strlen(var));
	if (is_exit_code)
		free(var);
	if (!(*s_exp))
		return (0);
	return (len);
}

char *ex_expand_var_block(char **envp, t_token *t)
{
	char	*s_exp;
	size_t	i;

	i = 0;
	s_exp = NULL;
	while (i < t->content_len)
	{
		if (t->content[i] == '$')
		{
			i += ex_expand_var(envp, t, i, &s_exp);
			if (!s_exp)
			{
				free(s_exp);
				return (NULL);
			}
		}
		i++;
	}
	if (s_exp[0] == 0)
		t->padding = 0;
	t->content = s_exp;
	t->content_len = ft_strlen(s_exp);
	t->kind = TOKEN_ALLOC;
	return (s_exp);
}



// QUOTE Stuff
static void ex_step_into_quote(t_token *t)
{
	if (t->content[0] == '"' || t->content[0] == '\'')
	{
		t->content++;
		t->content_len -= 2;
		t->kind = TOKEN_TEXT;
		if (t->content_len == 0)
			t->padding = 0;
	}
}

char *expand_var(char **envp, t_token *t, size_t i)
{
	char	*var;
	size_t	len;

	len = 0;
	if (i + 1 >= t->content_len)
		var = "$";	
	else
	{
		len = ex_var_len(t->content + i + 1);
		var = ex_find_var(envp, t->content + i + 1, len);
		if (!var)
			var = "";
	}
	return (var);
}

t_token ex_expand_quote_block(char **envp, t_token *t)
{
	t_exp 	exp;
	exp = ex_pack_struct(t, envp);
	ex_step_into_quote(exp.t);

	while (exp.t->content && exp.t->content[exp.i])
	{
		if (!ex_iterate(&exp))
		{
			printf("ex_iterate failed\n");
		}
		exp.i += exp.step;
		if (exp.end == exp.t->content + exp.t->content_len)
			break;
	}
	return lx_token_set(TOKEN_ALLOC, exp.s_exp, ft_strlen(t->content));
};

bool	ex_main(char **envp, t_tok_list *tokens)
{
	t_token	*t;

	while (tokens)
	{
		t = &tokens->token;
		if (t->kind == TOKEN_QUOTE_DOUBLE)
		{
			tokens->token = ex_expand_quote_block(envp, t);
			if (tokens->token.kind == TOKEN_ERROR)
				return (false);
		}
		else if (t->kind == TOKEN_QUOTE_SINGLE)
			ex_step_into_quote(t);
		else if (t->kind == TOKEN_BLOCK_DOLLAR)
		{
			if (!ex_expand_var_block(envp, t))
				return (false);
		}
		tokens = tokens->next;
	}
	return (true);
}
