/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plarser.c                                         :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 12:26:52 by jboeve            #+#    #+#             */
/*   Updated: 2023/09/22 22:31:18 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "plarser.h"
#include "test_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include "megashell.h"
#include "utils.h"



t_cmd_list *plarser_main(t_meta *meta, char *line)
{
	t_tok_list *tokens;

	t_cmd_list *cmds;
	tokens = lx_main(line);
	if (!tokens)
	{
		printf("lexer malloc failure\n");
		return (NULL);
	}
	print_tokens(tokens);
	// TODO expansion before syntax check.
	tokens = ex_main(meta->envp, tokens);
	if (!tokens)
	{
		printf("expander failed\n");
		lx_lst_free(tokens);
		return (NULL);

	}
	t_tok_list *err = sy_main(tokens);
	if (err)
	{
		printf("syntax error at token '%.*s'\n", err->token.content_len, err->token.content);
		lx_lst_free(tokens);
		return (NULL);
	}
	cmds = pr_main(tokens);
	lx_lst_free(tokens);

	return (cmds);
}
