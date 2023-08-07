/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:29:30 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/08/07 18:13:36 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

void	dup_cmd(t_exec *execute, t_cmds *cmds)
{
	if (cmds->prev && dup_stdin(execute->pipes_fd[IN]) == false)
		print_error(get_error_name(ERROR_DUP2));
	if (cmds->next && dup_stdout(execute->pipes_fd[OUT]) == false)
		print_error(get_error_name(ERROR_DUP2));
}

void	children_spawn(t_exec *execute, t_cmds *cmds)
{
	// redirects();
	// builtins();
	if (find_access(execute, cmds) == false)
		print_error(get_error_name(ERROR_ACCESS));
	dup_cmd(execute, cmds);
}

void	start_pipe(t_exec *execute, t_cmds *cmds)
{
	while (cmds->next)
	{
		if (pipe(execute->pipes_fd) == -1)
		{
			print_error(get_error_name(ERROR_PIPE));
			return ;
		}
		execute->pid = fork();
		if (execute->pid == -1) /* fork returns -1 in case of error*/
		{
			print_error(get_error_name(ERROR_FORK));
			return ;
		}
		if (execute->pid == 0) /* fork returns 0 for child process */
			children_spawn(execute, cmds);
		cmds = cmds->next;
	}
}

// void	single_child()
// {
	
// }

void	execution(t_exec *execute, t_cmds *list)
{
	int		pipes_fd[2];
	int		prev_pipe;
	int		status;
	t_cmds	*cmds;

	cmds = list;
	// heredoc?	
//	if (cmds->next == 0) /* && is_it_builtin(cmds->action[i]) == true) */
//		single_child(); /*  afhankelijk van builtin */
	if (cmds->next)
		start_pipe(execute, cmds);
}
