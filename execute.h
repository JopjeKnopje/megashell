/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:04:59 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/08/02 12:43:10 by ivan-mel         ###   ########.fr       */
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

typedef enum e_files {
	READ,
	WRITE,
}	t_files;

typedef enum e_error {
	ERROR_ARGUMENTS,
	ERROR_PATH,
	ERROR_FIND_PATH,
	ERROR_PIPE,
	ERROR_FORK,
	ERROR_DUP2,
}	t_error;

typedef struct s_pipes{
	int	pipes;
}	t_pipes;

typedef struct s_cmds {
	char			**action;
	struct s_cmds	*next;
}	t_cmds;

typedef struct s_exec {
	int		args;
	int		pid;
	char	**argv;
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
int		search_path(t_exec *execute, char **envp);

// environment:
char	**get_environment(char **envp);

// execute :
void	execute(t_exec *execute, t_cmds *list);

// execute_utils:
int		dup_stdin(int file);
int		dup_stdout(int file);

// free:
void	free_2d(char **str);

// list:
t_cmds	*mock_input(void);

#endif
