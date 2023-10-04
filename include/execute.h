/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                         :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:04:59 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/10/04 14:30:30 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

#include "megashell.h"
# include "libft.h"
# include "builtins.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/stat.h>
# include <sys/types.h>

typedef enum e_files {
	PIPE_READ,
	PIPE_WRITE,
}	t_files;

typedef	enum e_access {
	CHECK_DIR,
	CHECK_ACCESS,
}	t_access;

typedef enum e_error {
	ERROR_ARGUMENTS,
	ERROR_PATH,
	ERROR_FIND_PATH,
	ERROR_PIPE,
	ERROR_FORK,
	ERROR_DUP2,
	ERROR_ACCESS,
	ERROR_ALLOC,
	ERROR_DOT,
}	t_error;

// error:
char		*get_error_name(t_error er);
int			print_error(char *str);

// path:
char	*find_path(char **envp);
char		**split_path(char *path);
char		**put_slash(char **path);
int	search_path(t_meta *meta, char **environment);

// environment:
char		**get_environment(char **envp);

// execute:
bool		execute(t_meta *meta, t_cmd_list *list);

// execute_utils:
bool		dup_stdin(int file);
bool		dup_stdout(int file);
void		dup_io(t_exec *execute, t_cmd_list *cmds);

// builtins:
t_builtin	get_builtin(char *cmd);
bool	run_builtin(t_builtin builtin, t_meta *meta, t_cmd_list *cmds);

// access:
bool	find_access(t_meta *meta, t_cmd_list *cmds);
bool		is_a_directory(char *cmd);
char		*check_relative_path(char *cmd);
char	*find_executable_in_path(char **split_path, char *cmd);
char	*access_possible(t_meta *meta, char *cmd);

// free:
void		free_2d(char **str);

// list:
t_cmd_list	*create_mock_node(char *argv[4]);
void		add_to_end(t_cmd_list **list, t_cmd_list *new);
t_cmd_list	*mock_input(void);

#endif
