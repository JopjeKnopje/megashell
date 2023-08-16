/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   parser.h                                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <marvin@42.fr>                       +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/08/14 16:40:07 by jboeve        #+#    #+#                 */
/*   Updated: 2023/08/16 10:57:48 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#ifndef PARSER_H
#define PARSER_H

#include <stdint.h>
#include "lexer.h"

typedef enum e_io_flags {
	IO_STDOUT 	= 1 << 0,
	IO_STDIN  	= 1 << 1,
	IO_INFILE 	= 1 << 2,
	IO_OUTFILE	= 1 << 3,
	IO_APPEND 	= 1 << 4,
	IO_PIPE 	= 1 << 5,
} t_io_flags;

// if infile and outfile are set read from them otherwise just stdin/stdout
// if `is_piped` is set it overrules the outfile.
typedef struct s_command_frame {
	char	**argv;
	char	*infile;
	char	*outfile;
	uint8_t io_flags;
} t_command_frame;

typedef struct e_cf_list {
	t_command_frame		content;
	struct e_cf_list	*next;
	struct e_cf_list	*prev;
}	t_cf_list;

typedef struct e_parser {
	t_command_frame		frame;
	t_cf_list			*command_frames;

}	t_parser;

// parser.c
uint32_t pr_count_argv(t_tok_list *tok_list, t_token_kind k);


// parser_jmp.c
t_tok_list *pr_parse_token(t_parser *p, t_tok_list *current_token);

// parser_list.c
void		pr_lstadd_back(t_cf_list **lst, t_cf_list *new);
t_cf_list	*pr_lstnew(t_command_frame content);
t_cf_list	*pr_lstlast(t_cf_list *lst);
t_cf_list	*pr_list_add_token(t_cf_list **cf_list, t_command_frame frame);
void pr_lst_free(t_cf_list *lst, void (*func)(t_cf_list *node));

#endif // !PARSER_H
