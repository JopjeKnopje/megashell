/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plarser.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:40:07 by jboeve            #+#    #+#             */
/*   Updated: 2023/09/18 14:53:00 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PLARSER_H
#define PLARSER_H

#include "libft.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdint.h>

typedef enum e_token_kind {
	TOKEN_UNKNOWN 		= 0,
	TOKEN_QUOTE_SINGLE 	= 1, // '[content]'
	TOKEN_QUOTE_DOUBLE 	= 2, // "[content]"
	TOKEN_DOLLAR 		= 3, // $
	TOKEN_PIPE 			= 4, // |
	TOKEN_LESS_THAN 	= 5, // <
	TOKEN_GREATER_THAN 	= 6, // >
	TOKEN_APPEND 		= 7, // >>
	TOKEN_HEREDOC 		= 8, // <<
	TOKEN_TEXT 			= 9,
	TOKEN_ERROR 		= 10,
	TOKEN_COUNT 		= 11,
}	t_token_kind;

typedef struct e_token {
	t_token_kind	kind;
	uint32_t		content_len;
	char			*content;
}	t_token;


/*
   there should be a field for redirections.
infile: 
	stdin | default

	inflie_name
	heredoc

outfile:
	stdout | default

	outfile_name
	outfile_name out_append


using it:
	if infile/outfile is not set, then there is not redirection.
	if is_heredoc isset then the outfile will be the deliminter.

*/
typedef struct s_cmd_frame {
	char	**argv;
	char	*infile;
	char	*outfile;
	bool	is_append;
	bool	is_heredoc;
} t_cmd_frame;


typedef struct e_token_list {
	t_token				token;
	struct e_token_list	*next;
	struct e_token_list	*prev;
}	t_tok_list;


typedef struct e_cmd_list {
	t_cmd_frame			content;
	struct e_cmd_list	*next;
	struct e_cmd_list	*prev;
}	t_cmd_list;


// parser.c
t_cmd_list		*pr_main(t_tok_list *tokens);

// parser_list.c
t_cmd_list		*pr_lstnew(t_cmd_frame content);
t_cmd_list		*pr_lstlast(t_cmd_list *lst);
void			pr_lst_free(t_cmd_list *lst);
void			pr_lstadd_back(t_cmd_list **lst, t_cmd_list *new);
void			pr_lstiter(t_cmd_list *lst, void (*f)(t_cmd_list *));

// syntax.c
t_tok_list		*sy_main(t_tok_list *tokens);

// syntax_func.c
bool			sy_token_redir(t_tok_list *token);
bool			sy_token_quote(t_tok_list *token);
bool			sy_token_variable(t_tok_list *token);
bool			sy_token_pipe(t_tok_list *token);
bool			sy_token_pass(t_tok_list *node);
bool			sy_token_err(t_tok_list *node);

// lexer.c
t_tok_list		*lx_main(char *s);

// lexer_utils.c
bool			lx_is_metachar(char c);
bool			lx_is_varchar(char c);
bool			lx_is_valid_var_name(char *s);
bool			lx_is_redir_heredoc(char *s, t_token_kind k);

// lexer_list.c
void			lx_lstadd_back(t_tok_list **lst, t_tok_list *new);
t_tok_list		*lx_lstnew(t_token content);
t_tok_list		*lx_lstlast(t_tok_list *lst);
void			lx_lst_free(t_tok_list *lst);

// tokenize.c
t_token			lx_token_set(t_token_kind k, char *s, uint32_t len);
t_token			lx_tokenize_quote(char *s, char c);
t_token			lx_tokenize_dollar(char *s);
t_token			lx_tokenize_text(char *s);

#endif
