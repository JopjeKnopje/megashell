/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   parser.h                                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <marvin@42.fr>                       +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/08/14 16:40:07 by jboeve        #+#    #+#                 */
/*   Updated: 2023/08/14 16:50:55 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#ifndef PARSER_H
#define PARSER_H


typedef enum e_io {
	REDIR_STDOUT = 0x0000,
	REDIR_PIPE = 0x0001,
	REDIR_STDIN = 0x0020,
} t_io;

// 0000


// if infile and outfile are set read from them otherwise just stdin/stdout
// if `is_piped` is set it overrules the outfile.
typedef struct s_command_frame {
	char **argv;
	char *infile;
	char *outfile;
	t_io io;

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
