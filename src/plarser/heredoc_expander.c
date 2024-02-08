/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   heredoc_expander.c                                :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/02/03 22:09:57 by joppe         #+#    #+#                 */
/*   Updated: 2024/02/06 00:16:03 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "expander.h"
#include "libft.h"
#include "megashell.h"
#include "plarser.h"
#include <stddef.h>
#include "utils.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

static char	*poep(size_t *i, char *s_line, char *s)
{
	s_line = ex_str_append(s_line, s + (*i), 1);
	(*i)++;
	return (s_line);
}

char	*hd_exp(t_meta *meta, char *s)
{
	t_token	t;
	size_t	i;
	char	*s_exp;
	char	*s_line;

	i = 0;
	s_line = NULL;
	s_exp = NULL;
	while (s[i])
	{
		if (s[i] == '$')
		{
			t = lx_tokenize_dollar_block((char *) s + i);
			i += t.content_len;
			if (t.kind != TOKEN_ERROR)
				s_exp = ex_expand_var_block(meta->envp, &t);
			else
				s_exp = "";
			s_line = ex_str_append(s_line, s_exp, strlen(s_exp));
			free(s_exp);
		}
		else
			s_line = poep(&i, s_line, s);
	}
	return (s_line);
}
