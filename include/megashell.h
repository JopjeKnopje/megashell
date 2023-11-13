/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   megashell.h                                       :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <jboeve@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/09/19 11:40:37 by jboeve        #+#    #+#                 */
/*   Updated: 2023/11/13 22:12:24 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEGASHELL_H
#define MEGASHELL_H

#include <fcntl.h>
#include <stdbool.h>
#include "libft.h"
#include "plarser.h"

#define HISTORY_FILE_NAME	".ms_history"
#define HEREDOC_PROMPT		"\033[36;49m>\033[0m "
// #define SHELL_PROMPT		"\033[mmegashell> "
#define SHELL_PROMPT		"\033[32;49mmegashell>\033[0m "

typedef struct s_exec {
	int			args;
	int			pid;
	int			io_file[2];
	char		**argv;
	char		**split_path;
}	t_exec;


typedef struct s_meta {
	char	**envp;
	t_exec	execute;
} t_meta;



// megashell.c
int megashell(int argc, char *argv[], char *envp[]);

// plarser.c
t_cmd_list *plarser_main(char **envp, char *line);

// prompt.c
void	prompt_env_setup();
char	*prompt_get_line();

// history_file.c
void hs_read_history_file(char *s);
void hs_add_history_file(char *s, char *line);

// aliases.c
void aliases_init(t_meta *meta);

#endif // !MEGASHELL_H
