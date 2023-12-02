/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                           :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: iris <iris@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:03:58 by joppe             #+#    #+#             */
/*   Updated: 2023/12/02 23:51:34 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
#define INPUT_H

#include "megashell.h"

typedef	enum e_signal {
	MAIN,
	CHILD,
	HEREDOC,
	IGNORE,
}	t_signal;

typedef struct s_alias {
	char *key;
	char *value;
}	t_alias;

typedef struct e_alias_list {
	t_alias				alias;
	struct e_alias_list	*next;
}	t_alias_list;

// signals.c
void	signals_setup(int mode);

// prompt.c
const char *get_prompt(int exit_code);


#endif // !INPUT_H
