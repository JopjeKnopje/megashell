/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   lexer.h                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/07/31 17:15:13 by joppe         #+#    #+#                 */
/*   Updated: 2023/08/15 16:20:22 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include "libft.h"
#include <stdint.h>
#include <stdbool.h>

typedef enum e_token_kind {
	TOKEN_UNKNOWN,
	TOKEN_QUOTE_SINGLE,
	TOKEN_QUOTE_DOUBLE,
	TOKEN_DOLLAR,
	TOKEN_PIPE,
	TOKEN_LESS_THAN,
	TOKEN_GREATER_THAN,
	TOKEN_TEXT,
	TOKEN_ERROR,
	TOKEN_COUNT,
}	t_token_kind;

static const char *TOKEN_NAMES[] = {
	"TOKEN_UNKNOWN",
	"TOKEN_QUOTE_SINGLE",
	"TOKEN_QUOTE_DOUBLE",
	"TOKEN_DOLLAR",
	"TOKEN_PIPE",
	"TOKEN_LESS_THAN",
	"TOKEN_GREATER_THAN",
	"TOKEN_TEXT",
	"TOKEN_ERROR",
	"TOKEN_COUNT",
};

typedef struct e_token {
	t_token_kind	kind;
	uint32_t		content_len;
	char			*content;
}	t_token;

typedef struct e_token_list {
	t_token				content;
	struct e_token_list	*next;
	struct e_token_list	*prev;
}	t_token_list;




/**************************
* Included in megashell.h *
**************************/
// void	lexer(char *s);

// lexer_utils.c
bool	lx_is_metachar(char c);
bool	lx_is_varchar(char c);
bool	lx_is_valid_var_name(char *s);

// lexer_list.c
void			lx_lstadd_back(t_token_list **lst, t_token_list *new);
t_token_list	*lx_lstnew(t_token content);
t_token_list	*lx_lstlast(t_token_list *lst);

// tokenize.c
t_token	lx_token_set(t_token_kind k, char *s, uint32_t len);
t_token	lx_tokenize_quote(char *s, char c);
t_token	lx_tokenize_dollar(char *s);
t_token	lx_tokenize_text(char *s);

#endif
