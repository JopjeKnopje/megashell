/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 12:34:54 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/08/22 14:42:32 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

bool	find_access(t_exec *execute, t_cmd_list *cmds)
{
	char	*cmd_in_path;

	cmd_in_path = access_possible(execute, cmds->content.argv[0]);
	if (!cmd_in_path)
		return (false);
	if (execve (cmd_in_path, cmds->content.argv, execute->envp) == -1)
		return (false);
	return (true);
}

char	*access_possible(t_exec *execute, char *cmd)
{
	int		i;
	char	*tmp;

	i = 0;
	while (execute->split_path[i])
	{
		tmp = ft_strjoin(execute->split_path[i], cmd);
		if (!tmp)
			return (NULL);
		if (access(tmp, F_OK) == 0)
		{
			// printf("cmd: %s\n", tmp);
			return (tmp);
		}
		free(tmp);
		i++;
	}
	return (NULL);
}
