/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                         :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:31:17 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/12/03 00:46:06 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
#define HEREDOC_H

#include "megashell.h"
#include "plarser.h"
#include "builtins.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>


typedef struct e_heredoc_list {
	int 					fd;
	struct e_heredoc_list	*next;
}	t_hd_list;


// redirections.c
bool	redirections(t_cmd_frame *f, t_hd_list **heredocs);

// heredoc_list.c
void 		hd_lst_free(t_hd_list *lst);
void		hd_lstadd_back(t_hd_list **lst, t_hd_list *new);
t_hd_list	*hd_lstremove_first(t_hd_list **lst);
t_hd_list	*hd_lstlast(t_hd_list *lst);
t_hd_list	*hd_lstnew(int fd);

// heredoc.c
bool		contains_heredoc(t_cmd_list *cmds);
int			handle_heredoc(t_cmd_frame *f, int *status);
t_hd_list	*append_heredoc(t_hd_list **head, int heredoc_fd);
t_hd_list	*run_heredocs(t_cmd_list *cmds);

#endif
