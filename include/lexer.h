/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   lexer.h                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/07/31 17:15:13 by joppe         #+#    #+#                 */
/*   Updated: 2023/08/04 19:11:30 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include <stdint.h>
#include <stdbool.h>

typedef enum e_token_kind {
	TOKEN_UNKNOWN,
	TOKEN_QUOTE_SINGLE,
	TOKEN_QUOTE_DOUBLE,
	TOKEN_SPACE,
	TOKEN_COMMAND,
	TOKEN_DOLLAR,
	TOKEN_ERROR,
	TOKEN_COUNT,
}	t_token_kind;

static const char *TOKEN_NAMES[] = {
	"TOKEN_UNKNOWN",
	"TOKEN_QUOTE_SINGLE",
	"TOKEN_QUOTE_DOUBLE",
	"TOKEN_SPACE",
	"TOKEN_COMMAND",
	"TOKEN_DOLLAR",
	"TOKEN_ERROR",
	"TOKEN_COUNT",
};

typedef struct e_token {
	t_token_kind	kind;
	uint32_t		content_len;
	char			*content;
}	t_token;


typedef struct e_lexer {

	char			*cursor;
}	t_lexer;


// lexer.c
void	lexer(char *s);

// lexer_utils.c
bool	lexer_is_metachar(char c);
bool	lexer_is_varchar(char c);

#endif
