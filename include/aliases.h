/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   aliases.h                                         :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/08/29 10:42:36 by joppe         #+#    #+#                 */
/*   Updated: 2023/08/29 11:02:44 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALIASES_H
#define ALIASES_H

#include "megashell.h"


/**
  * When launching the shell it will go through a set of files
  * and source all their aliases.
  * TODO Add custom file as launch argument.
  */


// aliases.c
void al_init(t_meta *meta);

// aliases_list.c
t_alias_list	*al_lstnew(t_alias content);
t_alias_list	*al_lstlast(t_alias_list *lst);
void			al_lst_free(t_alias_list *lst);
void			al_lstadd_back(t_alias_list **lst, t_alias_list *new);
t_alias_list *al_list_add_alias(t_alias_list **alias_list, t_alias alias);
#endif
