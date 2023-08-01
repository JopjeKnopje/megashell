/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:29:30 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/08/01 14:16:41 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

void	execute(t_exec *execute, t_cmds *list)
{
	int		pipes_fd[2];
	t_cmds	*cmds;

	cmds = list;
	while (cmds)
	{
		if (pipe(pipes_fd) == -1)
			return (print_error(get_error_name(ERROR_PIPE)));
		
	}
	waitpid(execute->pid, &status, 0);
	while (wait(NULL) != -1)
		continue ;
	return ((WEXITSTATUS(status)));
}
