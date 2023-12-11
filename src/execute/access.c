/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 12:34:54 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/12/11 13:41:53 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "megashell.h"
#include "utils.h"

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
			printf("megashell: ./: is a directory\n");
			exit (126);
		}
	}
	else if (status == CHECK_ACCESS)
	{
		if (access(cmd, F_OK | X_OK) != 0)
		{
			printf("megashell: %s: No such file or directory\n", cmd);
			exit (127);
		}
		if (!cmd)
		{
			printf("megashell: %s: command not found", cmd);
			exit (127);
		}
	}
	return ;
}

char	*check_relative_path(char *cmd, char *buffer)
{
	int		i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
		{
			buffer = ft_strdup(cmd);
			if (!buffer)
				return (NULL);
			exit_errors(buffer, CHECK_ACCESS);
			return (buffer);
		}
		i++;
	}
	return (buffer);
}

bool	check_existing_path(t_meta *meta)
{
	char	**s;

	s = search_in_path(meta->envp, "PATH=");
	if (!s)
	{
		if (execve(meta->execute.argv[0], meta->execute.argv, meta->envp) == -1)
		{
			printf("%s: No such file or directory\n", meta->execute.argv[0]);
			return (false);
		}
	}
	free_2d(s);
	return (true);
}

char	*access_possible(t_meta *meta, char *cmd)
{
	char	*cmd_copy;
	char	*executable_path;

	cmd_copy = NULL;
	if (!cmd)
		return (NULL);
	if (cmd[0] == '.' && cmd[1] == '\0')
	{
		print_error(get_error_name(ERROR_DOT));
		exit(2);
	}
	exit_errors(cmd, CHECK_DIR);
	cmd_copy = check_relative_path(cmd, cmd_copy);
	if (cmd_copy)
		return (cmd_copy);
	if (!check_existing_path(meta))
		return (NULL);
	executable_path = find_executable_in_path(meta->execute.split_path, cmd);
	if (!executable_path)
	{
		printf("megashell: %s: command not found\n", cmd);
		exit(127);
	}
	return (executable_path);
}
