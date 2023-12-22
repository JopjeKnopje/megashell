/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                   :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:10:33 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/12/08 17:58:00 by jboeve        ########   odam.nl         */
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

	variable = cmd->argv[1];
	if (!cmd->argv[1])
		return (0);
	if (!remove_env_variable(meta->envp, variable))
		return (0);
	return (0);
}
