/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   syntax.c                                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/08/18 21:20:04 by joppe         #+#    #+#                 */
/*   Updated: 2023/08/18 22:06:47 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "plarser.h"



static bool sy_check(t_tok_list *node)
{

}

t_syntax_error sy_main(t_tok_list *tokens)
{
	while (tokens)
	{
		sy_check(tokens);

		tokens = tokens->next;
	}

	return (lx_token_set(TOKEN_UNKNOWN, TOKEN_NAMES[TOKEN_UNKNOWN], ft_strlen(TOKEN_NAMES[TOKEN_UNKNOWN])));
}
