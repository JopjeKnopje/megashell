/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:58:16 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/08/28 16:32:17 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "builtins.h"

bool	add_to_env(t_exec *execute, t_cmd_list *cmds, char *cmd_start)
{
	int		i;
	int		j;
	char	**new_envp;

	i = 0;
	j = 0;
	while (execute->envp[i])
		i++;
	new_envp = ft_calloc(sizeof(char *), i + 2);
	if (!new_envp)
	{
		printf("Memory allocation error\n");
		free(cmd_start);
		return (false);
	}
	while (j < i)
	{
		new_envp[j] = ft_strdup(execute->envp[j]);
		if (!new_envp[j])
		{
			free(cmd_start);
			while (j > 0)
			{
				j--;
				free(new_envp[j]);
			}
			free(new_envp);
			return (false);
		}
		j++;
	}
	new_envp[i] = ft_strdup(cmds->content.argv[1]);
	if (!new_envp[i])
	{
		free(cmd_start);
		free_2d(new_envp);
		printf("Memory allocation error\n");
		return (false);
	}
	free_2d(execute->envp);
	execute->envp = new_envp;
	return (true);
}
