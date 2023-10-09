/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                   :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:10:33 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/10/04 15:21:16 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "megashell.h"
#include "plarser.h"

void	print_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		printf("%s\n", envp[i]);
		i++;
	}
}

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
			printf("Comparing '%s' with '%s'\n", envp[i], variable);
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
		printf("Not Enough Arguments\n");
		return (false);
	}
	printf("Before unset:\n");
	print_envp(meta->envp);
	if (remove_env_variable(meta->envp, variable) == false)
		return (false);
	printf("After unset:\n");
	print_envp(meta->envp);
	return (true);
}
