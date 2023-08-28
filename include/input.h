/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   input.h                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/07/31 16:03:58 by joppe         #+#    #+#                 */
/*   Updated: 2023/08/28 18:19:20 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
#define INPUT_H

#include "megashell.h"

typedef struct s_alias {
	char *key;
	char *value;
}	t_alias;

typedef struct e_alias_list {
	t_alias				alias;
	struct e_alias_list	*next;
}	t_alias_list;

// signals.c
void	sigals_setup();


#endif // !INPUT_H
