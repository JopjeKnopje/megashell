/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plarser.c                                         :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 12:26:52 by jboeve            #+#    #+#             */
/*   Updated: 2023/12/11 17:38:32 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "plarser.h"
#include "execute.h"
#include "test_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

static bool	contains_error(t_tok_list *tokens)
{
	while (tokens)
	{
		if (tokens->token.kind == TOKEN_ERROR)
			return (true);
		tokens = tokens->next;
	}
	return (false);
}

static void	*handle_error(t_tok_list *tokens, t_token *err, int *error)
{
	set_exit_code(2);
	printf("syntax error at token '%.*s'\n", \
			(int) err->content_len, err->content);
	lx_lst_free(tokens);
	*error = 0;
	return (NULL);
}

t_cmd_list	*plarser_main(char **envp, char *line, int *error)
{
	t_tok_list	*tokens;
	t_cmd_list	*cmds;
	t_tok_list	*err;

	tokens = lx_main(line);
	if (!tokens)
	{
		print_error(get_error_name(ERROR_LEXER));
		return (NULL);
	}
	tokens = sc_main(tokens);
	if (!contains_error(tokens) && !ex_main(envp, tokens))
		return (NULL);
	err = sy_main(tokens);
	if (err)
		return (handle_error(tokens, &err->token, error));
	cmds = pr_main(tokens);
	lx_lst_free(tokens);
	if (!cmds)
		return (NULL);
	return (cmds);
}
