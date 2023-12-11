/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plarser.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:40:07 by jboeve            #+#    #+#             */
/*   Updated: 2023/12/11 17:10:59 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLARSER_H

# define PLARSER_H

# include "libft.h"
# include <stdint.h>
# include <stdbool.h>
# include <stdint.h>

typedef enum e_token_kind {
	TOKEN_UNUSED 				= 0,
	TOKEN_QUOTE_SINGLE 	= 1,	// '[content]'
	TOKEN_QUOTE_DOUBLE 	= 2,	// "[content]"
	TOKEN_BLOCK_DOLLAR 			= 3,	// $
	TOKEN_PIPE 					= 4,	// |
	TOKEN_LESS_THAN 			= 5,	// <
	TOKEN_GREATER_THAN 			= 6,	// >
	TOKEN_APPEND 				= 7,	// >>
	TOKEN_HEREDOC 				= 8,	// <<
	TOKEN_TEXT 					= 9,
	TOKEN_ALLOC					= 10, 	// We know its allocated memory this only happens in the expander.
	TOKEN_ERROR 				= 11, 	// Error which the syntax checker will handle
	TOKEN_COUNT 				= 12,
}	t_token_kind;

typedef struct s_token {
	t_token_kind	kind;
	size_t			content_len;
	size_t			padding;
	char			*content;
}	t_token;

typedef struct s_cmd_frame {
	char	**argv;
	char	*infile;
	char	*outfile;
	char	*heredoc_delim;
	bool	is_append;
}	t_cmd_frame;

typedef struct e_token_list {
	t_token				token;
	struct e_token_list	*next;
	struct e_token_list	*prev;
}	t_tok_list;

typedef struct e_cmd_list {
	t_cmd_frame			content;
	int					pid;
	int					pipe[2];
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
size_t			pr_lst_count(t_cmd_list *lst);

// space_count.c
t_tok_list		*sc_main(t_tok_list *tokens);

// expander.c
bool			ex_main(char **envp, t_tok_list *tokens);

// syntax.c
t_tok_list		*sy_main(t_tok_list *tokens);

// syntax_func.c
bool			sy_token_redir(t_tok_list *token);
bool			sy_token_quote(t_tok_list *token);
bool			sy_token_variable(t_tok_list *token);
bool			sy_token_pipe(t_tok_list *token);
bool			sy_token_pass(t_tok_list *node);
bool			sy_token_err(t_tok_list *node);
bool			sy_token_unused(t_tok_list *node);

// parser_joiner.c
t_tok_list		*pr_joiner(t_tok_list *tokens);

// lexer.c
t_tok_list		*lx_list_add_token(t_tok_list **token_lst, t_token t);
t_tok_list		*lx_main(char *s);

// lexer_utils.c
bool			lx_is_metachar(char c);
bool			lx_is_varchar(char c);
bool			lx_is_valid_var_char(char c, bool first_letter);
bool			lx_is_valid_var_name(char *s);
bool			lx_is_redir_heredoc(char *s, t_token_kind k);

// lexer_list.c
void			lx_lstadd_back(t_tok_list **lst, t_tok_list *new);
t_tok_list		*lx_lstnew(t_token content);
t_tok_list		*lx_lstlast(t_tok_list *lst);
void			lx_lst_free(t_tok_list *lst);

// tokenize.c
t_token			lx_token_set(t_token_kind k, char *s, uint32_t len);
t_token			lx_tokenize_quote_block(char *s, char c);
t_token			lx_tokenize_dollar_block(char *s);
t_token			lx_tokenize_text(char *s);

#endif
