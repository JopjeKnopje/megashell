/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:34:16 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/07/31 18:02:53 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

// fix own environment later (linkedlist?)

char	*find_path(char **envp)
{
	char	*path;

	path = getenv("PATH");
	return (path);
}

char	**split_path(char *path)
{
	char	**path2;

	if (!path)
		return (NULL);
	path2 = ft_split(path, ':');
	if (!path2)
		return (NULL);
	return (path2);
}

char	**put_slash(char **path)
{
	char	*temp;
	int		index;

	index = 0;
	while (path[index])
	{
		temp = ft_strjoin(path[index], "/");
		if (!temp)
		{
			free_2d(path);
			return (NULL);
		}
		free(path[index]);
		path[index] = temp;
		index++;
	}
	return (path);
}

int	search_path(t_exec *execute, char **envp)
{
	char	*path;
	char	**path_after_split;

	execute->envp = get_environment(envp);
	path = find_path(execute->envp);
	path_after_split = split_path(path);
	if (!path_after_split)
		return (print_error(get_error_name(ERROR_PATH)));
	execute->split_path = put_slash(path_after_split);
	if (!execute->split_path)
		return (print_error(get_error_name(ERROR_PATH)));
	return (EXIT_SUCCESS);
}
