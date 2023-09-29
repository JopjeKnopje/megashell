/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   expander.c                                        :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/09/22 22:22:44 by joppe         #+#    #+#                 */
/*   Updated: 2023/09/29 21:48:14 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "plarser.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

static t_token ex_expand_token(char **envp, t_token t)
{
	char *key;

	key = envp_find_var(envp, t.content + 1, t.content_len - 1);
	if (!key)
	{
		t.content = "";
		t.content_len = 0;
		return (t);
	}
	if (*key == '=')
		key++;

	t.content = key;
	t.content_len = ft_strlen(key);
	t.kind = TOKEN_TEXT;
	return (t);
}


t_tok_list *ex_main(char **envp, t_tok_list *tokens)
{
	t_tok_list	*head = tokens;
	char		*value;

	while (tokens)
	{
		if (tokens->token.kind == TOKEN_VARIABLE)
		{
			char *tmp = sized_strdup(tokens->token.content, tokens->token.content_len);
			tokens->token = ex_expand_token(envp, tokens->token);
			printf("expanded [%s] -> [%.*s]\n", tmp, tokens->token.content_len, tokens->token.content);
			free(tmp);
		}
		tokens = tokens->next;
	}
	return (head);
}
