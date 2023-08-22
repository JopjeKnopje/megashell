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
#include "libft.h"
#include "plarser.h"

#define HISTORY_FILE_NAME ".ms_history"

typedef struct s_meta {
	bool stop;
} t_meta;



// megashell.c
int megashell(int argc, char *argv[], char *envp[]);

// plarser.c
t_cmd_list *plarser_main(char *line);

// prompt.c
void	prompt_env_setup();
char	*prompt_get_line();

// history_file.c
void hs_read_history_file(char *s);
void hs_add_history_file(char *s, char *line);

#endif // !MEGASHELL_H
