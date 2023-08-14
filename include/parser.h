/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   parser.h                                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <marvin@42.fr>                       +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/08/14 16:40:07 by jboeve        #+#    #+#                 */
/*   Updated: 2023/08/14 18:13:40 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#ifndef PARSER_H
#define PARSER_H

#include <stdint.h>

typedef enum e_io_flags {
	IO_STDOUT 	= 0x0001,
	IO_STDIN  	= 0x0002,
	IO_INFILE 	= 0x0004,
	IO_OUTFILE	= 0x0008,
	IO_APPEND 	= 0x0010,
	IO_PIPE 	= 0x0020,
} t_io_flags;

// if infile and outfile are set read from them otherwise just stdin/stdout
// if `is_piped` is set it overrules the outfile.
typedef struct s_command_frame {
	char **argv;
	char *infile;
	char *outfile;
	uint8_t io;

} t_command_frame;

typedef struct e_cf_list {
	t_command_frame		content;
	struct e_cf_list	*next;
}	t_cf_list;


// parser_list.c
void		pr_lstadd_back(t_cf_list **lst, t_cf_list *new);
t_cf_list	*pr_lstnew(t_command_frame content);
t_cf_list	*pr_lstlast(t_cf_list *lst);

#endif // !PARSER_H
