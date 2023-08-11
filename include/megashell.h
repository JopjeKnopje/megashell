/*                                                       ::::::::             */
/*   megashell.h                                       :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <marvin@42.fr>                       +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/07/24 12:09:29 by jboeve        #+#    #+#                 */
/*   Updated: 2023/07/31 16:46:03 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEGASHELL_H
#define MEGASHELL_H

#include <stdbool.h>
#include "libft.h"

typedef struct s_meta {
	bool stop;
} t_meta;

// megashell.c
int megashell(int argc, char *argv[], char *envp[]);

// lexer.c
t_list *lexer(char *s);

// lexer_utils.c
bool lexer_is_valid_var_name(char *s);

#endif // !MEGASHELL_H
