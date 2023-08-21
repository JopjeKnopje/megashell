/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:10:33 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/08/21 13:25:18 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

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

bool	builtin_run_unset(t_exec *execute, t_cmd_list *cmds)
{
	char	*variable;

	variable = cmds->action[1];
	if (!cmds->action[1])
	{
		printf("Not Enough Arguments\n");
		return (false);
	}
	printf("Before unset:\n");
	print_envp(execute->envp);
	if (remove_env_variable(execute->envp, variable) == false)
		return (false);
	printf("After unset:\n");
	print_envp(execute->envp);
	return (true);
}
