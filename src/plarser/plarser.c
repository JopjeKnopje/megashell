/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plarser.c                                         :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 12:26:52 by jboeve            #+#    #+#             */
/*   Updated: 2023/12/02 17:40:57 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "plarser.h"
#include "execute.h"
#include "test_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"


static bool contains_error(t_tok_list *tokens)
{
	while (tokens)
	{
		if (tokens->token.kind == TOKEN_ERROR)
			return (true);
		tokens = tokens->next;
	}
	return (false);
}

t_cmd_list *plarser_main(char **envp, char *line)
{
	t_tok_list *tokens;
	t_cmd_list *cmds;

	tokens = lx_main(line);
	if (!tokens)
	{
		printf("lexer malloc failure\n");
		return (NULL);
	}

	// count spaces LOL
	tokens = sc_main(tokens);


	print_tokens(tokens);
	if (contains_error(tokens))
		goto syntax_check;

	// printf("\n\n\n\n\n\n");

	if (!ex_main(envp, tokens))
	{
		UNIMPLEMENTED("ex_main failed");
	}


syntax_check:
	printf("\n\n\n\n\n\n\n\n");
	print_tokens(tokens);
	t_tok_list *err = sy_main(tokens);
	if (err)
	{
		set_exit_code(2);
		printf("syntax error at token '%.*s'\n", (int) err->token.content_len, err->token.content);
		lx_lst_free(tokens);
		return (NULL);
	}
	cmds = pr_main(tokens);
	lx_lst_free(tokens);

	return (cmds);
}
