/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   lexer.h                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/07/31 17:15:13 by joppe         #+#    #+#                 */
/*   Updated: 2023/08/02 18:19:07 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H


#include <stdint.h>
typedef enum e_token_kind {
	TOKEN_UNKNOWN,
	TOKEN_QUOTE_SINGLE,
	TOKEN_QUOTE_DOUBLE,

}	t_token_kind;

static const char *TOKEN_NAMES[] = {
	"TOKEN_UNKNOWN",
	"TOKEN_QUOTE_SINGLE",
	"TOKEN_QUOTE_DOUBLE",
};

typedef struct e_token {
	t_token_kind	kind;
	uint32_t		content_len;
	char			*content;
}	t_token;


typedef struct e_lexer {

	char			*content;
}	t_lexer;


// lexer.c
void	lexer(char *s);

#endif // !LEXER_H
