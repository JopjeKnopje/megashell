/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iris <iris@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:29:30 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/08/06 00:31:22 by iris             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

int	check_input(t_exec *execute, int pipes_fd[2], int prev_pipe)
{
	int	fd_in;
	if (prev_pipe == STDIN_FILENO) /* first child */
	{
		close(pipes_fd[READ]);
		fd_in = open(execute->argv[0], O_RDONLY); /* infile is stdin */
		if (fd_in == -1)
			return (print_error(strerror(errno)));
		close(fd_in);
		
	}
	else if (prev_pipe != STDIN_FILENO) /* redirect prev pipe to stdin */
	{
		dup_stdin(prev_pipe);
		close(prev_pipe);
	}
	return (0);
}

int	check_output(t_exec *execute, int pipes_fd[2], int prev_pipe)
{
	int	fd_out;
	if (pipes_fd[WRITE] == STDOUT_FILENO) /* last child */
	{
		close(pipes_fd[WRITE]);
		fd_out = open(execute->argv[execute->argc - 1],
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_out == -1)
			return (print_error(strerror(errno)));
		dup_stdout(fd_out);
		close(fd_out);
	}
	else if (pipes_fd[WRITE] != STDOUT_FILENO) /* not sure about this check tomorrow */
	{
		dup_stdout(pipes_fd[WRITE]);
	}
	return (0);
}

bool	find_access(t_exec *execute, t_cmds *list)
{
	char *cmd;
	char *cmd_in_path;
	int	i;

	i = 0;
	cmd = ft_strdup(execute->split_path[i]);
	if (!cmd)
		return (false);
	cmd_in_path = access_possible(execute, &cmd[0]);
	if (!cmd_in_path)
		return (false);
		if (execve (cmd_in_path, &execute->split_path[i], execute->envp) == -1)
			return (false);
	return (true);
}

void	children_spawn(t_exec *execute, int pipes_fd[2], int prev_pipe, t_cmds *list)
{
	check_input(execute, pipes_fd, prev_pipe);
	check_output(execute, pipes_fd, prev_pipe);
	if (find_access(execute, list) == false)
		print_error(get_error_name(ERROR_ACCESS));
}

char	execution(t_exec *execute, t_cmds *list)
{
	int		pipes_fd[2];
	int		prev_pipe;
	int		status;
	t_cmds	*cmds;

	cmds = list;
	prev_pipe = STDIN_FILENO;
	while (cmds)
	{
		if (pipe(pipes_fd) == -1)
			return (print_error(get_error_name(ERROR_PIPE)));
		execute->pid = fork();
		if (execute->pid == -1) /* fork returns -1 in case of error*/
			return (print_error(get_error_name(ERROR_FORK)));
		if (execute->pid == 0) /* fork returns 0 for child process */
			children_spawn(execute, pipes_fd, prev_pipe, list);
		cmds = cmds->next; /* goes to next command*/
	}
	waitpid(execute->pid, &status, 0);
	while (wait(NULL) != -1)
		continue ;
	return ((WEXITSTATUS(status)));
}
