/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plarser.c                                         :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 12:26:52 by jboeve            #+#    #+#             */
/*   Updated: 2023/08/29 17:17:31 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "plarser.h"
#include "test_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"



t_cmd_list *plarser_main(char *line)
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
