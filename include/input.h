/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iris <iris@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:03:58 by joppe             #+#    #+#             */
/*   Updated: 2023/11/25 13:56:44 by iris             ###   ########.fr       */
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

void	signals_setup(int mode);


#endif // !INPUT_H
