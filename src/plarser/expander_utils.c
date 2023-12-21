/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   expander_utils.c                                  :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <jboeve@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/12/12 18:46:47 by jboeve        #+#    #+#                 */
/*   Updated: 2023/12/13 01:13:11 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "libft.h"
#include "plarser.h"
#include <stddef.h>

static int	ft_abs(int x)
{
	const uint32_t	temp = x >> 31;

	x ^= temp;
	x += temp & 1;
	return (x);
}

t_exp	ex_pack_struct(t_token *t, char **envp)
{
	t_exp	exp;

	ft_bzero(&exp, sizeof(t_exp));
	exp.t = t;
	exp.envp = envp;
	return (exp);
}

static bool	ex_iterate_append(t_exp *exp)
{
	char	*var_exp;

	var_exp = expand_var(exp->envp, exp->t, exp->i);
	exp->step = ex_var_len(exp->t->content + exp->i);
	if (exp->step)
	{
		exp->s_exp = ex_str_append(exp->s_exp, var_exp, ft_strlen(var_exp));
		if (!exp->s_exp)
			return (false);
	}
	return (true);
}

static bool	ex_iterate_skip(t_exp *exp)
{
	char		*var_exp;
	const char	*closing_quote = ft_strchr(exp->t->content + exp->i, '"');

	exp->end = ft_strchr(exp->t->content + exp->i, '$');
	if (!exp->end || exp->end > closing_quote)
		exp->end = exp->t->content + exp->t->content_len;
	var_exp = ft_substr(exp->t->content + exp->i, 0,
			ft_abs(exp->t->content + exp->i - exp->end));
	if (!var_exp)
	{
		free(exp->s_exp);
		return (false);
	}
	exp->step = ft_strlen(var_exp);
	exp->s_exp = ex_str_append(exp->s_exp, var_exp, exp->step);
	free(var_exp);
	return (true);
}

bool	ex_iterate(t_exp *exp)
{
	if (exp->t->content[exp->i] == '$')
	{
		if (!ex_iterate_append(exp))
		{
			return (false);
		}
	}
	else
	{
		if (!ex_iterate_skip(exp))
		{
			return (false);
		}
	}
	return (true);
}
