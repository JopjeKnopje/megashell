/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   expander_utils2.c                                 :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/12/14 01:44:03 by joppe         #+#    #+#                 */
/*   Updated: 2024/01/21 21:41:52 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "plarser.h"

size_t	get_key_len(char *key)
{
	size_t	i;

	i = 0;
	while (key[i] && key[i] != '=')
	{
		i++;
	}
	return (i);
}

char	*ex_find_var(char **envp, char *name, size_t len)
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

void	ex_step_into_quote(t_token *t)
{
	if (t->content[0] == '"' || t->content[0] == '\'')
	{
		t->content++;
		t->content_len -= 2;
		if (t->content_len == 0)
			t->padding = 0;
	}
	t->kind = TOKEN_TEXT;
}
