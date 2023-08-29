/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 12:34:54 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/08/29 15:40:04 by ivan-mel         ###   ########.fr       */
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

bool	is_a_directory(char *cmd)
{
	struct stat	stat_of_cmd;

	if (stat(cmd, &stat_of_cmd) != 0)
		return (false);
	if (S_ISDIR(stat_of_cmd.st_mode))
		return (true);
	return (false);
}

char	*access_possible(t_exec *execute, char *cmd)
{
	int		i;
	char	*tmp;
	char	*cmd_copy;

	i = 0;

	// error handling
	// X_OK
	if (!cmd)
		return (NULL);
	if (cmd[0] == '.' && cmd[1] == '\0')
	{
		print_error(get_error_name(ERROR_DOT));
		exit (2);
	}
	if (is_a_directory(cmd) == true)
		printf("bash: ./: is a directory\n");
	while (cmd[i])
	{
		if (cmd[i] == '/')
		{
			cmd_copy = ft_strdup(cmd);
			if (!cmd_copy)
			{
				print_error(get_error_name(ERROR_ALLOC));
				exit (EXIT_FAILURE);
			}
			if (access(cmd_copy, F_OK) == 0)
				return (cmd_copy);
		}
		i++;
	}
	i = 0;
	while (execute->split_path[i])
	{
		tmp = ft_strjoin(execute->split_path[i], cmd);
		if (!tmp)
			return (NULL);
		if (access(tmp, F_OK) == 0)
		{
			printf("access?\n");
			return (tmp);
		}
		free(tmp);
		i++;
	}
	return (NULL);
}
