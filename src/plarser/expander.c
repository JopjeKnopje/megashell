/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   expander.c                                        :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/09/22 22:22:44 by joppe         #+#    #+#                 */
/*   Updated: 2023/09/30 15:46:16 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "plarser.h"
#include "utils.h"
#include <ctype.h>
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

static bool ex_is_quoted_var(t_token *t)
{
	int i = 1;

	if (t->kind != TOKEN_QUOTE_DOUBLE)
		return (false);
	if (t->content_len <= 2)
		return (false);

	while (t->content[i] != '$')
		i++;

	printf("found var: [%.*s]\n", t->content_len - i - 1, &t->content[i]);
	return (true);
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
		else if (ex_is_quoted_var(&tokens->token))
		{
			tokens->token = ex_expand_token(envp, tokens->token);
		}
		tokens = tokens->next;
	}
	return (head);
}
