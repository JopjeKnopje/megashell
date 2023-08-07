/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:04:59 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/08/07 17:14:53 by ivan-mel         ###   ########.fr       */
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

typedef enum e_files {
	IN,
	OUT,
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

typedef struct s_pipes{
	int	pipes;
}	t_pipes;

typedef struct s_cmds {
	char			**action;
	struct s_cmds	*next;
	struct s_cmds	*prev;
}	t_cmds;

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

char	*get_error_name(t_error er);
int		print_error(char *str);

// path:
char	*find_path(t_exec *execute);
char	**split_path(char *path);
char	**put_slash(char **path);
int		search_path(t_exec *execute, char **environment);

// environment:
char	**get_environment(char **envp);

// execute:
int		check_input(t_exec *execute, int pipes_fd[2],
			int prev_pipe, t_cmds *cmds);
int		check_output(t_exec *execute, int pipes_fd[2], int prev_pipe);
void	start_pipe(t_exec *execute, t_cmds *cmds);
void	children_spawn(t_exec *execute, t_cmds *cmds);
void	execution(t_exec *execute, t_cmds *list);

// execute_utils:
bool	dup_stdin(int file);
bool	dup_stdout(int file);

// access:
bool	find_access(t_exec *execute, t_cmds *list);
char	*access_possible(t_exec *execute, char *list);

// free:
void	free_2d(char **str);

// list:
t_cmds	*mock_input(void);

#endif
