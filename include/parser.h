/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   parser.h                                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/08/14 10:05:49 by joppe         #+#    #+#                 */
/*   Updated: 2023/08/14 10:10:45 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#ifndef PARSER_H
#define PARSER_H

typedef struct s_command_frame {
	char **argv;
	int infile;
	int outfile;
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
