/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:03:58 by joppe             #+#    #+#             */
/*   Updated: 2023/12/11 16:42:50 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include "megashell.h"

typedef enum e_signal {
	MAIN,
	CHILD,
	HEREDOC,
	IGNORE,
}	t_signal;

typedef struct s_alias {
	char	*key;
	char	*value;
}	t_alias;

typedef struct e_alias_list {
	t_alias				alias;
	struct e_alias_list	*next;
}	t_alias_list;

// signals.c
bool		set_signal_mode(int mode);

// prompt.c
const char	*get_prompt(int exit_code);

#endif
