/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   lexer.c                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/07/31 16:57:13 by joppe         #+#    #+#                 */
/*   Updated: 2023/07/31 18:56:35 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdio.h>
#include "lexer.h"

t_token lexer(char *s)
{
	uint32_t i = 0;
	t_token t;

	printf("lexer input: %s\n", s);

	while (s[i]) 
	{
		
	}

	return t;
}
