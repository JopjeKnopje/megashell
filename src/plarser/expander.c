/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                        :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 23:35:50 by joppe             #+#    #+#             */
/*   Updated: 2024/01/23 19:31:56 by joppe         ########   odam.nl         */
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
	int32_t ret =(((!(*s_exp)) != 0) * 0 + ((!(!(*s_exp)) != 0) + 1));
	return ret;
}

char	*ex_expand_var_block(char **envp, t_token *t)
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
			printf("s_exp [%s]\n", s_exp);
			if (!s_exp)
				return (NULL);
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

char	*expand_var(char **envp, t_token *t, size_t i)
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

t_token	ex_expand_quote_block(char **envp, t_token *t)
{
	t_exp	exp;
	t_token ret_tok;

	exp = ex_pack_struct(t, envp);
	ex_step_into_quote(exp.t);
	while (exp.t->content && exp.t->content[exp.i])
	{
		if (!ex_iterate(&exp))
		{
			print_error("ex_iterate failed\n");
		}
		exp.i += exp.step;
		if (exp.end == exp.t->content + exp.t->content_len)
			break ;
	}
	ret_tok = lx_token_set(TOKEN_ALLOC, exp.s_exp, ft_strlen(exp.s_exp));
	ret_tok.padding = t->padding;
	return (ret_tok);
}

bool	ex_main(char **envp, t_tok_list *tokens)
{
	t_token	*t;

	while (tokens)
	{
		t = &tokens->token;
		if ((tokens->prev && tokens->prev->token.kind == TOKEN_HEREDOC) \
				&& (t->kind == TOKEN_QUOTE_DOUBLE || t->kind == TOKEN_QUOTE_SINGLE || t->kind == TOKEN_BLOCK_DOLLAR))
			ex_step_into_quote(t);
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
