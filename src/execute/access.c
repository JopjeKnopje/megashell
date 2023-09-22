/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 12:34:54 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/09/22 16:07:56 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "megashell.h"

bool	find_access(t_meta *meta, t_cmd_list *cmds)
{
	char	*cmd_in_path;

	cmd_in_path = access_possible(meta, cmds->content.argv[0]);
	if (!cmd_in_path)
		return (false);
	if (execve (cmd_in_path, cmds->content.argv, meta->envp) == -1)
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

void	exit_errors(char *cmd, int status)
{
	if (status == CHECK_DIR)
	{
		if (is_a_directory(cmd) == true)
		{
			printf("bash: ./: is a directory\n");
			exit (126);
		}
	}
	else if (status == CHECK_ACCESS)
	{
		if (access(cmd, F_OK | X_OK) != 0)
		{
			printf("bash: %s: No such file or directory\n", cmd);
			exit (127);
		}
		if (!cmd)
		{
			printf("bash: %s: command not found", cmd);
			exit (127);
		}
	}
	return ;
}

char	*check_relative_path(char *cmd)
{
	int		i;
	char	*cmd_copy;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
		{
			cmd_copy = ft_strdup(cmd);
			exit_errors(cmd_copy, CHECK_ACCESS);
			return (cmd_copy);
		}
		i++;
	}
	return (NULL);
}

char	*access_possible(t_meta *meta, char *cmd)
{
	char	*cmd_copy;
	char	*executable_path;

	if (!cmd)
		return (NULL);
	if (cmd[0] == '.' && cmd[1] == '\0')
	{
		print_error(get_error_name(ERROR_DOT));
		exit(2);
	}
	exit_errors(cmd, CHECK_DIR);
	cmd_copy = check_relative_path(cmd);
	if (cmd_copy)
		return (cmd_copy);
	executable_path = find_executable_in_path(meta->execute.split_path, cmd);
	if (!executable_path)
	{
		printf("bash: %s: command not found\n", cmd);
		exit(127);
	}
	return (executable_path);
}
