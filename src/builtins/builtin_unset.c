/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:10:33 by ivan-mel          #+#    #+#             */
/*   Updated: 2024/01/19 17:55:01 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static bool	remove_env_variable(char **envp, const char *variable)
{
	int	i;
	int	len_var;

	i = 0;
	len_var = ft_strlen(variable);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], variable, len_var) == 0
			&& (envp[i][len_var] == '='))
		{
			free(envp[i]);
			while (envp[i] != NULL)
			{
				envp[i] = envp[i + 1];
				i++;
			}
			return (true);
		}
		i++;
	}
	return (false);
}

int	builtin_run_unset(t_meta *meta, t_cmd_frame *cmd)
{
	char	*variable;
	char	*path;
	
	variable = cmd->argv[1];
	if (!cmd->argv[1])
		return (0);
	if (!remove_env_variable(meta->envp, variable))
		return (0);
	path = find_path(meta->envp);
	if (!path)
	{
		free(meta->execute.split_path);
		meta->execute.split_path = NULL;
	}
	return (0);
}
