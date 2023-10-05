/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iris <iris@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:10:33 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/10/05 12:20:54 by iris             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "megashell.h"
#include "plarser.h"

bool	remove_env_variable(char **envp, const char *variable)
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
			// printf("Comparing '%s' with '%s'\n", envp[i], variable);
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

bool	builtin_run_unset(t_meta *meta, t_cmd_frame *cmd)
{
	char	*variable;

	variable = cmd->argv[1];
	if (!cmd->argv[1])
	{
		// printf("Not Enough Arguments\n");
		return (false);
	}
	if (remove_env_variable(meta->envp, variable) == false)
		return (false);
	return (true);
}
