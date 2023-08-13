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

#include <fcntl.h>
#include <stdbool.h>
#include "lexer.h"
#include "libft.h"

typedef struct s_meta {
	bool stop;
} t_meta;


// forward decl for token_list
typedef struct e_token_list t_token_list;


// megashell.c
int megashell(int argc, char *argv[], char *envp[]);

// prompt.c
void	prompt_env_setup();
char	*prompt_get_line();

// lexer.c
t_token_list *lx_main(char *s);

// parser.c
void	pr_main(t_token_list *tok_list);

#endif // !MEGASHELL_H
