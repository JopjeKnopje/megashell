/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:29:30 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/08/02 12:45:04 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

void	check_input(t_exec *execute, int pipes_fd[2])
{
	int	fd;
	if (FD)
	{
		close(pipes[READ]);
		fd = open(execute->argv[0], O_RDONLY);
		if (fd == -1)
			return (print_error(strerror(errno)));
		dup_stdin(fd);
		dup_stdout(pipes_fd[WRITE]);
		
	}
	if (PIPE)
	{
		
	}
}

void	check_output()
{
	
}

void	children_spawn(t_exec *execute, int piped_fd[2])
{
	check_input();
	check_output();
}

void	execute(t_exec *execute, t_cmds *list)
{
	int		pipes_fd[2];
	t_cmds	*cmds;

	cmds = list;
	while (cmds)
	{
		if (pipe(pipes_fd) == -1)
			return (print_error(get_error_name(ERROR_PIPE)));
		execute->pid = fork();
		if (execute->pid == -1) /* fork returns -1 in case of error*/
			return (print_error(get_error_name(ERROR_FORK)));
		if (execute->pid == 0) /* fork returns 0 for child process */
			children_spawn(execute, pipes_fd);
		cmds = cmds->next; /* goes to next command*/
	}
	waitpid(execute->pid, &status, 0);
	while (wait(NULL) != -1)
		continue ;
	return ((WEXITSTATUS(status)));
}
