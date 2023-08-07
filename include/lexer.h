/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   lexer.h                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/07/31 17:15:13 by joppe         #+#    #+#                 */
/*   Updated: 2023/08/07 19:18:52 by jboeve        ########   odam.nl         */
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


/**************************
* Included in megashell.h *
**************************/
// void	lexer(char *s);



// lexer_utils.c
bool	lexer_is_metachar(char c);
bool	lexer_is_varchar(char c);

// tokenize.c
t_token token_set(t_token_kind k, char *s, uint32_t len);
t_token lexer_tokenize_quote(char *s, char c);
t_token lexer_tokenize_dollar(char *s);

// tokenize_utils.c
bool	tokenize_is_valid_var_name(char *s);



#endif
