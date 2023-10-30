/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   expander.c                                        :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/29 23:35:50 by joppe         #+#    #+#                 */
/*   Updated: 2023/10/30 20:18:20 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "plarser.h"
#include <stdio.h>

char *ex_find_var(char **envp, char *name)
{
	size_t	i = 0;
	char	*var;

	if (*name == '$')
		name++;

	while (envp[i])
	{
		if (!ft_strncmp(envp[i], name, ft_strlen(name)))
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

void ex_expand_var(char **envp, t_token *t)
{
	char *exp = ex_find_var(envp, t->content);
	printf("expanding [%.*s] -> [%s]\n", t->content_len, t->content, exp);
}

bool ex_main(char **envp, t_tok_list *tokens)
{
	t_token t;
	
	while (tokens)
	{
		t = tokens->token;
		if (t.kind == TOKEN_DOLLAR || t.kind == TOKEN_QUOTE_DOUBLE)
		{
			ex_expand_var(envp, &t);
		}
	

		tokens = tokens->next;
	}


	return (true);
}
