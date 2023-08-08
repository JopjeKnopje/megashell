/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iris <iris@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:04:59 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/08/08 23:32:12 by iris             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <stdbool.h>

// redirections:
// INFILE = <
// OUTFILE = >
// APPEND = >>
// HEREDOC = <<

# define INFILE 0
# define OUTFILE 1
# define APPEND 2
# define HEREDOC 3


typedef enum e_files {
	IN_READ,
	OUT_WRITE,
}	t_files;

typedef enum e_error {
	ERROR_ARGUMENTS,
	ERROR_PATH,
	ERROR_FIND_PATH,
	ERROR_PIPE,
	ERROR_FORK,
	ERROR_DUP2,
	ERROR_ACCESS,
}	t_error;

typedef struct s_redir{
	int	type;
}	t_redir;

typedef struct s_cmd_list {
	char				**action;
	struct s_cmds_list	*next;
	struct s_cmds_list	*prev;
	t_redir				redirect;
}	t_cmd_list;

//cmds_list

typedef struct s_exec {
	int		args;
	int		argc;
	int		pid;
	int		pipes_fd[2];
	char	**argv;
	char	*infile;
	char	*outfile;
	char	**envp;
	char	**split_path;

}	t_exec;

// error:
char		*get_error_name(t_error er);
int			print_error(char *str);

// path:
char		*find_path(t_exec *execute);
char		**split_path(char *path);
char		**put_slash(char **path);
int			search_path(t_exec *execute, char **environment);

// environment:
char		**get_environment(char **envp);

// execute:
void		dup_io(t_exec *execute, t_cmd_list *cmds);
void		children_spawn(t_exec *execute, t_cmd_list *cmds);
void		start_pipe(t_exec *execute, t_cmd_list *cmds);
void		execution(t_exec *execute, t_cmd_list *list);

// execute_utils:
bool		dup_stdin(int file);
bool		dup_stdout(int file);

// access:
bool		find_access(t_exec *execute, t_cmd_list *list);
char		*access_possible(t_exec *execute, char *list);

// free:
void		free_2d(char **str);

// list:
t_cmd_list	*create_mock_node(char *action[4]);
void		add_to_end(t_cmd_list **list, t_cmd_list *new);
t_cmd_list	*mock_input(void);

#endif
