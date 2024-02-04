/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   heredoc_expander.c                                :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/02/03 22:09:57 by joppe         #+#    #+#                 */
/*   Updated: 2024/02/04 02:38:35 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "libft.h"
#include "megashell.h"
#include "plarser.h"
#include <stddef.h>
#include "utils.h"
#include <stdint.h>
#include <stdio.h>
#include "test_utils.h"



static size_t	strlen_null(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
	{
		i++;
	}
	return (i);
}

static char	*sized_strjoin1(char *s1, size_t l1, char *s2, size_t l2)
{
	char	*buf;
	size_t	total_size;

	total_size = l1 + l2 + 1;
	buf = ft_calloc(total_size, sizeof(char));
	if (!buf)
		return (NULL);
	if (!s1)
		s1 = ft_calloc(1, sizeof(char));
	ft_bzero(buf, total_size);
	ft_strlcpy(buf, s1, l1 + 1);
	ft_strlcat(buf, s2, total_size);
	free(s1);
	return (buf);
}


char *hd_exp(t_meta *meta, char *s)
{
	t_token	t;
	size_t	i = 0;
	char	*s_exp = NULL;

	while (s[i])
	{
		if (s[i] == '$')
		{
			t = lx_tokenize_dollar_block((char *) s + i);
			print_token(t);

			s_exp = sized_strjoin1(s_exp, strlen_null(s_exp), t.content, t.content_len);

			i += t.content_len;
		}
		else
		{
			s_exp = sized_strjoin1(s_exp, strlen_null(s_exp), s + i, 1);
			i++;
		}
	}
	return s_exp;
}
