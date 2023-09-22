/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   pipes_test.h                                      :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/09/23 00:46:40 by joppe         #+#    #+#                 */
/*   Updated: 2023/09/23 01:12:13 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPES_TEST_H
#define PIPES_TEST_H

typedef struct s_command {
	int		pipe[2];
	int 	id;
	char	*data;
} t_command;

typedef struct e_test_list {
	t_command 			*cmd;
	struct e_test_list	*next;
	struct e_test_list	*prev;
}	t_test_list;


t_test_list	*test_lstlast(t_test_list *lst);
t_test_list	*test_lstnew(t_command *content);
void		test_lstadd_back(t_test_list **lst, t_test_list *new);
void		test_lst_free(t_test_list *lst);
void		test_lstiter(t_test_list *lst, void (*f)(t_test_list *));



int pipes_test();

#endif // !pipes_test_h
