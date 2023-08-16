/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   plarser.h                                         :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <marvin@42.fr>                       +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/08/14 16:40:07 by jboeve        #+#    #+#                 */
/*   Updated: 2023/08/16 16:10:00 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#ifndef PLARSER_H
#define PLARSER_H

#include "libft.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdint.h>

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

typedef enum e_io_flags {
	IO_STDOUT 	= 1 << 0,
	IO_STDIN  	= 1 << 1,
	IO_INFILE 	= 1 << 2,
	IO_OUTFILE	= 1 << 3,
	IO_APPEND 	= 1 << 4,
	IO_PIPE 	= 1 << 5,
} t_io_flags;

typedef struct e_token {
	t_token_kind	kind;
	uint32_t		content_len;
	char			*content;
}	t_token;

typedef struct e_token_list {
	t_token				token;
	struct e_token_list	*next;
	struct e_token_list	*prev;
}	t_tok_list;


typedef struct s_cmd_frame {
	char	**argv;
	char	*infile;
	char	*outfile;
	uint8_t io_flags;
} t_cmd_frame;

typedef struct e_cmd_frame_list {
	t_cmd_frame				content;
	struct e_cmd_frame_list	*next;
	struct e_cmd_frame_list	*prev;
}	t_cf_list;

typedef struct e_parser {
	t_cmd_frame		frame;
	t_cf_list		*command_frames;

}	t_parser;



// lexer_utils.c
bool		lx_is_metachar(char c);
bool		lx_is_varchar(char c);
bool		lx_is_valid_var_name(char *s);

// lexer_list.c
void		lx_lstadd_back(t_tok_list **lst, t_tok_list *new);
t_tok_list	*lx_lstnew(t_token content);
t_tok_list	*lx_lstlast(t_tok_list *lst);
void		lx_lst_free(t_tok_list *lst);

// tokenize.c
t_token		lx_token_set(t_token_kind k, char *s, uint32_t len);
t_token		lx_tokenize_quote(char *s, char c);
t_token		lx_tokenize_dollar(char *s);
t_token		lx_tokenize_text(char *s);

// parser.c
void		pr_main(t_tok_list *tokens);
uint32_t	pr_run_parse(t_parser *p, t_tok_list *tokens);

// parser_list.c
void		pr_lstadd_back(t_cf_list **lst, t_cf_list *new);
t_cf_list	*pr_lstnew(t_cmd_frame content);
t_cf_list	*pr_lstlast(t_cf_list *lst);
t_cf_list	*pr_list_add_frame(t_cf_list **cf_list, t_cmd_frame frame);
void		pr_lst_free(t_cf_list *lst, void (*func)(t_cf_list *node));

#endif
